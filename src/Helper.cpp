#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

#include "../include/Helper.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::vector;
using std::stringstream;
using std::ifstream;
using std::unordered_map;
using std::unordered_multimap;

namespace fs = std::filesystem;

Helper::Helper() {}

/*
 * Comparators
 */

bool Helper::hash_comparator(const vector<string>& items, const File& data) {
    bool is_same_hash = false;
    if (std::to_string(data.file_hash) == items.at(db_pos::file_hash) && data.file == items.at(db_pos::file)) {
        is_same_hash = true;
    }
    return is_same_hash;
}

/*
 * Extractors
 */

void Helper::rows_extractor(vector<string>& rows, const string& target_file, const string& comparison_row) {
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        string target_file_row;
        if (comparison_row.empty()) {
            while (std::getline(target_file_istrm, target_file_row)) {
                rows.push_back(target_file_row);
            }
        } else {
            while (std::getline(target_file_istrm, target_file_row)) {
                if (target_file_row != comparison_row) {
                    rows.push_back(target_file_row);
                }
            }
        }
    } catch (const std::ios_base::failure& err) {
        if (!target_file_istrm.eof()) throw;
    }
    target_file_istrm.close();
    target_file_istrm.clear();
}

string Helper::row_extractor(const string& file, const string& target_file) {
    string extracted_row;
    vector<string> rows;
    rows_extractor(rows, target_file);
    for (const auto& row : rows) {
        string trimmed_file = row.substr(0, file.size());
        if (file == trimmed_file) {
            extracted_row = row;
            break;
        }
    }
    return extracted_row;
}

void Helper::items_extractor(vector<string>& items, const string& row, char separator) {
    string row_item;
    stringstream row_strm(row);
    while (std::getline(row_strm, row_item, separator)) {
        items.push_back(row_item);
    }
}

void Helper::items_extractor(vector<string>& items, const string& target_file, int item_position) {
    vector<string> rows;
    rows_extractor(rows, target_file);
    for (const auto& row : rows) {
        vector<string> db_items;
        items_extractor(db_items, row);
        items.push_back(db_items.at(item_position));
    }
}

/*
 * Checkers
 */

bool Helper::content_checker(const string& target_file) {
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    bool file_has_data = true;
    if (target_file_istrm.peek() == ifstream::traits_type::eof()) {
        file_has_data = false;
    }
    target_file_istrm.close();
    target_file_istrm.clear();
    return file_has_data;
}

template <typename T>
bool Helper::existence_checker(const T& file_or_files, const string& target_folder) { 
    bool exists = false;
    if constexpr (std::is_same_v<T, string>) {
        string file_to_check = target_folder + "/" + file_or_files;
        if (fs::exists(file_to_check)) {
            exists = true;
        }
    } else if constexpr (std::is_same_v<T, vector<string>>) {
        unsigned int match_counter = 0;
        for (const auto& file : file_or_files) {
            string file_to_check = target_folder + "/" + file;
            if (fs::exists(file_to_check)) {
                match_counter++;
            }
        }
        if (match_counter == file_or_files.size()) {
            exists = true;
        }
    }
    return exists;
}
template bool Helper::existence_checker<std::string>(const string&, const string&);
template bool Helper::existence_checker<std::vector<std::string>>(const vector<string>&, const string&);

// Este archivo es candidato para estandarizacion - Verificar si se usa en otros ambitos.
// Este archivo es candidato para estandarizacion - Verificar si se usa en otros ambitos. "file_record_checker" or some
bool Helper::ignored_file_checker(const string& file, const string& target_file) {
    bool is_ignored = false;
    vector<string> ignored_rows;
    rows_extractor(ignored_rows, target_file);
    for (const auto& ignored_item : ignored_rows) {
        string ignored_folder = file.substr(0, ignored_item.size());
        if (file == ignored_item || ignored_folder == ignored_item) {
            is_ignored = true;
        }
    }
    return is_ignored;
}

/*
 * Generators
 */

unsigned int  Helper::hash_generator(const string& target_file) {
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    string argumentfile_data_container {
        std::istreambuf_iterator<char>(target_file_istrm),
            std::istreambuf_iterator<char>()
    };
    unsigned int file_hash = 0;
    file_hash = std::hash<string> {}(argumentfile_data_container);
    target_file_istrm.close();
    target_file_istrm.clear();
    return file_hash;
}

void Helper::timepoint_generator(string& timepoint) {
    auto current_timepoint = std::chrono::system_clock::now();
    std::time_t formated_timepoint = std::chrono::system_clock::to_time_t(current_timepoint);
    char formated_timepoint_buffer[20];
    strftime(formated_timepoint_buffer, sizeof(formated_timepoint_buffer), "%H:%M:%S %d-%m-%Y", localtime(&formated_timepoint));
    timepoint = formated_timepoint_buffer;
}

/*
 * Organizers
 */

void Helper::data_organizer(File& data, const string& file) {
    data.file = file;
    data.file_hash = hash_generator(data.file);
    data.file_name = fs::path(data.file).filename().string();
    data.file_extension = fs::path(data.file).extension().string();

    if (data.file != data.file_name) {
        data.file_path = file.substr(0, (file.length() - data.file_name.length() - 1));
        data.file_path_hash = std::hash<string> {}(data.file_path);
    } else {
        data.file_path = "no_path";
        data.file_path_hash = 1000000000;
    }
    data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + data.file_extension;
}

void Helper::data_organizer(vector<File>& data_container, const vector<string>& rows, int mode) {
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& row : rows) {
        vector<string> items;
        items_extractor(items, row, ',');

        File data;
        data.file = items.at(db_pos::file);
        data.file_name = items.at(db_pos::file_name);
        data.file_extension = items.at(db_pos::file_extension);
        data.file_path = items.at(db_pos::path_name);
        data.file_path_hash = std::stoul(items.at(db_pos::path_hash));

        if (mode == action_mode::built) {
            data.file_hash = std::stoul(items.at(db_pos::file_hash));
            data.version_name = items.at(db_pos::version_name);
            data.catch_date = items.at(db_pos::catch_date);
        } else if (mode == action_mode::to_build) {
            data.file_hash = hash_generator(data.file);
            data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + data.file_extension;
            data.catch_date = temporal_date;
        }
        data_container.push_back(data);
    }
}

template<typename T> 
void Helper::data_organizer(vector<File>& data_container, const T& files) {
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& file : files) {
        File data;
        if constexpr (std::is_same_v<T,unordered_map<string,string>>) {
            data.file = file.second;
        } else if constexpr (std::is_same_v<T,vector<string>>) {
            data.file = file;
        }
        data.file_hash = hash_generator(data.file);
        data.file_name = fs::path(data.file).filename().string();
        data.file_extension = fs::path(data.file).extension().string();

        if (data.file != data.file_name) {
            data.file_path = data.file.substr(0, (data.file.length() - data.file_name.length() - 1));
            data.file_path_hash = std::hash<string> {}(data.file_path);
        } else {
            data.file_path = "no_path";
            data.file_path_hash = 1000000000;
        }
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + data.file_extension;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}

template void Helper::data_organizer<std::unordered_map<std::string,std::string>>(vector<File>&, const unordered_map<string,string>&);
template void Helper::data_organizer<std::vector<std::string>>(vector<File>&, const vector<string>&);


/*void Helper::data_organizer(vector<File>& data_container, const unordered_map<string,string>& files) {
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& file : files) {
        File data;
        data.file = file.second;
        data.file_hash = hash_generator(data.file);
        data.file_name = fs::path(data.file).filename().string();
        data.file_extension = fs::path(data.file).extension().string();

        if (data.file != data.file_name) {
            data.file_path = file.second.substr(0, (file.second.length() - data.file_name.length() - 1));
            data.file_path_hash = std::hash<string> {}(data.file_path);
        } else {
            data.file_path = "no_path";
            data.file_path_hash = 1000000000;
        }
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + data.file_extension;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}

void Helper::data_organizer(vector<File>& data_container, const vector<string>& files) {
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& file : files) {
        File data;
        data.file = file;
        data.file_hash = hash_generator(data.file);
        data.file_name = fs::path(data.file).filename().string();
        data.file_extension = fs::path(data.file).extension().string();

        if (data.file != data.file_name) {
            data.file_path = file.substr(0, (file.length() - data.file_name.length() - 1));
            data.file_path_hash = std::hash<string> {}(data.file_path);
        } else {
            data.file_path = "no_path";
            data.file_path_hash = 1000000000;
        }
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + data.file_extension;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}*/


// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
void Helper::available_files_organizer(unordered_map<string,string>& available_files, const vector<string>& rows, const string& current_path) {
    for (const auto& file_or_folder : fs::recursive_directory_iterator(current_path)) {
        if (!fs::is_directory(file_or_folder)) {
            unsigned int temp_counter = 0;
            string formatted_file = file_or_folder.path().string();
            string trimmed_file = formatted_file.erase(0, (current_path.size() + 1));

            for (auto& ignored_file : rows) {
                string comparison_file = trimmed_file.substr(0, ignored_file.size());
                if (ignored_file != comparison_file) { temp_counter++; }
            }

            unsigned int file_hash = 0;
            if (temp_counter == rows.size()) {
                file_hash = hash_generator(formatted_file);
                // Identificar donde se está usando esta función debido a que se ha generado un valor hash de un archivo con ruta incompleta (se uso erase sobre formatted_file)
                // Identificar donde se está usando esta función debido a que se ha generado un valor hash de un archivo con ruta incompleta (se uso erase sobre formatted_file)
                // Identificar donde se está usando esta función debido a que se ha generado un valor hash de un archivo con ruta incompleta (se uso erase sobre formatted_file)
                // Identificar donde se está usando esta función debido a que se ha generado un valor hash de un archivo con ruta incompleta (se uso erase sobre formatted_file)
                // Identificar donde se está usando esta función debido a que se ha generado un valor hash de un archivo con ruta incompleta (se uso erase sobre formatted_file)
                available_files.insert(make_pair(std::to_string(file_hash), trimmed_file));
            }
        }
    }
}

// ESTE AVAILABLE PUEDE ESPERAR ANTES DE SER UBIDO A SU HERMANO DE ARRIBA DEBIDO A QUE AUN NO ESTAMOS EN "RETURN":w
void Helper::available_files_folders_organizer(vector<string>& available_files, vector<string>& available_folders, const vector<string>& rows, const string& current_path) {
    for (const auto& file : fs::recursive_directory_iterator(current_path)) {
        unsigned int temp_counter = 0;
        string formatted_file = file.path().string();
        string trimmed_file = formatted_file.substr((current_path.size() + 1), formatted_file.size());

        for (auto& ignored_file : rows) {
            string comparison_file = trimmed_file.substr(0, ignored_file.size());
            if (ignored_file != comparison_file) { temp_counter++; } 
        }

        if (temp_counter == rows.size()) {
            if (fs::is_directory(formatted_file)) {
                available_folders.push_back(formatted_file);
            } else {
                available_files.push_back(formatted_file);
            }
        } 
    }
}



/*void Helper::vailable_files_organizer(vector<string>& popis, vector<string>& popos,
  const vector<string>& rows,
  const string& current_path) {
  for (const auto& folder : fs::recursive_directory_iterator(current_path)) {
  if (fs::is_directory(folder)) {
  unsigned int temp_counter = 0;
  string formatted_folder = folder.path().string();
  string trimmed_folder = formatted_folder.substr((current_path.size() + 1), formatted_folder.size());

  for (auto& ignored_file : rows) {
  string comparison_file = trimmed_folder.substr(0, ignored_file.size());
  if (ignored_file != comparison_file) {
  temp_counter++;
  }
  }

  string temp_folder_name = trimmed_folder.substr(0, trimmed_folder.find('/'));
  string folder_name = current_path + "/" + temp_folder_name;
  if (temp_counter == rows.size()) {
  popis.push_back(folder_name);
  std::sort(popis.begin(), popis.end());
  popis.erase(std::unique(popis.begin(), popis.end()), popis.end());
  } else {
  popos.push_back(folder_name);
  }
  }
  std::cout << ".........................." << std::endl;
  }
  }*/


/*void Helper::vailable_files_organizer(unordered_map<string,string>& untracked_files,
  const vector<string>& rows,
  const string& current_path) {
  for (auto& file : fs::recursive_directory_iterator(current_path)) {
  std::cout << "aqui a" << std::endl;
  unsigned int temp_counter = 0;
  string formatted_file = file.path().string();
  std::cout << "aqui b" << std::endl;
  fs::path p = formatted_file;
  std::cout << "aqui c" << std::endl;
  string parent = p.parent_path().string();
  std::cout << "aqui d" << std::endl;
  std::cout << "path -> " << parent << std::endl;
  std::cout << "aqui e" << std::endl;

//std::cout << "formated file -> " << formatted_file << std::endl;
string trimmed_file = parent.erase(0, (current_path.size() + 1));
std::cout << "trimmed -> " << trimmed_file << std::endl; 
std::cout << "aqui 1" << std::endl;
for (auto& ignored_file : rows) {
std::cout << "aqui 2" << std::endl;
string comparison_file = trimmed_file.substr(0, ignored_file.size());
std::cout << "aqui 3" << std::endl;
if (ignored_file != comparison_file) {
std::cout << "diferente" << std::endl;
temp_counter++;
} else {
std::cout << "diferente" << std::endl;
}
}

unsigned int file_hash = 0;
if (temp_counter == rows.size()) {
file_hash = hash_generator(formatted_file);
untracked_files.insert(make_pair(std::to_string(file_hash), trimmed_file));
}
std::cout << "-----------------------------------" << std::endl;
}
}*/


void Helper::status_organizer(unordered_map<string,string>& untracked_files, unordered_map<string,string>& modified_files, unordered_map<string,string>& saved_files, const string& target_file) {
    string trimmed_target_file = target_file.substr(target_file.size() - db_catch.size(), db_catch.size());
    vector<string> rows;
    rows_extractor(rows, target_file);
    unordered_map<string,string> temporal_files;
    
    if (trimmed_target_file == db_catch) {
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row, ',');
            temporal_files.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
        }
    } else {
        unordered_map<string,string> latest_version_checker;
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row, ',');
            for (auto latest_version_item : latest_version_checker) {
                if (items.at(db_pos::file) == latest_version_item.second) {
                    temporal_files.erase(latest_version_item.first);
                }
            }
            temporal_files.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
            latest_version_checker.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
        }
    }

    unsigned int hash_match_counter = 0;
    unsigned int filename_match_counter = 0;
    for (const auto& untracked_item : untracked_files) {
        for (const auto& saved_item : temporal_files) {
            if (untracked_item.second == saved_item.second) {
                saved_files.insert(make_pair(saved_item.first,saved_item.second));
                if (untracked_item.first != saved_item.first) {
                    modified_files.insert(make_pair(untracked_item.first,untracked_item.second));
                    hash_match_counter++;
                }
                filename_match_counter++;
                break;
            }
        }
    }

    if (filename_match_counter > 0) {
        for (const auto& item : saved_files) {
            untracked_files.erase(item.first);
        }
    }

    if (hash_match_counter > 0) {
        for (const auto& item : modified_files) {
            untracked_files.erase(item.first);
        }
    }
}

void Helper::log_organizer(Log& log, vector<Log>& log_info, unordered_multimap<string,string>& saved_files, const vector<string>& rows) {
    string temp_hash;
    string temp_date;
    string temp_comment;

    for (const auto& row : rows) {
        vector<string> items;
        items_extractor(items, row);

        saved_files.insert(make_pair(items.at(db_pos::snap_hash),items.at(db_pos::file)));
        if (temp_hash != items.at(db_pos::snap_hash)) {
            log.snapshot_code = items.at(db_pos::snap_hash);
            log.snapshot_date = items.at(db_pos::snap_date);
            log.snapshot_comment = items.at(db_pos::comment);
            log_info.push_back(log);
        }
        temp_hash = items.at(db_pos::snap_hash);
    }
}

void Helper::processed_files_organizer(vector<string>& saved_modified, vector<string>& saved_not_modified, const unordered_map<string,string>& modified_files, const unordered_map<string,string>& saved_files, const string& target_file) {
    for (auto saved_file : saved_files) {
        if (modified_files.empty()) {
            string temp_saved_not_modified = row_extractor(saved_file.second, target_file);
            saved_not_modified.push_back(temp_saved_not_modified );
        } else { 
            for (auto modified_file : modified_files) {
                if (saved_file.second == modified_file.second) {
                    string temp_saved_modified = row_extractor(saved_file.second, target_file);
                    saved_modified.push_back(temp_saved_modified);
                } else {
                    string temp_saved_not_modified = row_extractor(saved_file.second, target_file);
                    saved_not_modified.push_back(temp_saved_not_modified);
                }
            }
        }
    }

    std::sort(saved_not_modified.begin(), saved_not_modified.end());
    saved_not_modified.erase(std::unique(saved_not_modified.begin(), saved_not_modified.end()), saved_not_modified.end());

    for (auto item : saved_modified) {
        saved_not_modified.erase(std::remove(saved_not_modified.begin(), saved_not_modified.end(), item), saved_not_modified.end());
    }
}

void Helper::deception(vector<File>& datas, const string& target_folder, const string& current_path, const vector<string>& borra_folder) {
    for (auto data : datas) {
        string original_file = data.file;
        string temporal_file = target_folder  + "/" + data.version_name;
        fs::copy_file(original_file, temporal_file);
        fs::remove(original_file);
    }

    unsigned int conterolocos = 0;
    for (auto item : borra_folder) {
        for (const auto& file : fs::recursive_directory_iterator(item)) {
            if (!fs::is_directory(file)) {
                conterolocos++;
            }
        }

        if (conterolocos == 0) {
            fs::remove_all(item);
            conterolocos = 0;
        }
    }
}

Helper::~Helper() {}

