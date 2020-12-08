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

bool Helper::hash_comparator(const string& temporal_file_hash, const unsigned int& data_file_hash) {
    bool is_same_hash = false;
    if (std::to_string(data_file_hash) == temporal_file_hash) {
        is_same_hash = true;
    }
    return is_same_hash;
}

/*
 * Extractors
 */

void Helper::rows_extractor(vector<string>& rows, const string& target_file, const string& comparison_row, int mode, int item_position) {
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        string target_file_row;
        if (comparison_row.empty()) {
            while (std::getline(target_file_istrm, target_file_row)) {
                rows.push_back(target_file_row);
            }
        } else {
            if (mode == action_mode::different_to_row) {
                while (std::getline(target_file_istrm, target_file_row)) {
                    if (target_file_row != comparison_row) {
                        rows.push_back(target_file_row);
                    }
                }
            } else if (mode == action_mode::similar_to_item) {
                while (std::getline(target_file_istrm, target_file_row)) {
                    vector<string> extracted_items;
                    items_extractor(extracted_items, target_file_row);
                    if (extracted_items.at(item_position) == comparison_row) {
                        rows.push_back(target_file_row);
                    }
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

template<typename T, typename U>
void Helper::content_extractor(T& item_or_items, const U& target_container, int item_position) {
    if constexpr (std::is_same_v<T,string>) {
        vector<string> extracted_items;
        items_extractor(extracted_items, target_container);
        item_or_items = extracted_items.at(item_position);
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        vector<string> rows;
        if constexpr (std::is_same_v<U,string>) {
            rows_extractor(rows, target_container);
        } else if constexpr (std::is_same_v<U,vector<string>>) {
            rows = target_container;    
        }

        for (const auto& row : rows) {
            vector<string> extracted_items;
            items_extractor(extracted_items, row);
            item_or_items.push_back(extracted_items.at(item_position));
        }
    }
}
template void Helper::content_extractor<string, string>(string&, const string&, int);
template void Helper::content_extractor<vector<string>,string>(vector<string>&, const string&, int);
template void Helper::content_extractor<vector<string>,vector<string>>(vector<string>&, const vector<string>&, int);

/*template<typename T>
  void Helper::content_extractor(T& item_or_items, const string& target_container, int item_position) {
  if constexpr (std::is_same_v<T,string>) {
  vector<string> extracted_items;
  items_extractor(extracted_items, target_container);
  item_or_items = extracted_items.at(item_position);
  } else if constexpr (std::is_same_v<T,vector<string>>) {
  vector<string> rows;
  rows_extractor(rows, target_container);

  for (const auto& row : rows) {
  vector<string> extracted_items;
  items_extractor(extracted_items, row);
  item_or_items.push_back(extracted_items.at(item_position));
  }
  }
  }
  template void Helper::content_extractor<std::string>(string&, const string&, int);
  template void Helper::content_extractor<std::vector<std::string>>(vector<string>&, const string&, int);*/

/*
 * Checkers
 */

bool Helper::content_checker(const string& target_file) {
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    bool file_has_data = true;
    if (target_file_istrm.peek() == ifstream::traits_type::eof()) { file_has_data = false; }

    target_file_istrm.close();
    target_file_istrm.clear();

    return file_has_data;
}

// Función miembro: existence_checker(). 
// Permite validar la existencia de uno o muchos archivos.
template <typename T>
bool Helper::existence_checker(const T& file_or_files, unordered_map<string,bool>& status) { 
    bool exists = false;
    if constexpr (std::is_same_v<T,string>) {
        if (fs::exists(file_or_files)) {
            exists = true;
        }
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        unsigned int temp_counter = 0;
        // Recorremos la lista de archivos y se valida uno por uno su existencia
        // Si el archivo existe se incrementa un contador.
        // Adicionalmente se inserta el archivo en un unordered_map, junto con su estado respectivo (El estado que indica si el archivo existe o no)
        for (const auto& file : file_or_files) {
            if (fs::exists(file)) {
                temp_counter++;
                status.insert(make_pair(file,true));
            } else {
                status.insert(make_pair(file,false));
            }
        }
        
        // En caso el contador coincida con la cantidad de items del vector se puede asegurar que todos los archivos existen
        if (temp_counter == file_or_files.size()) {
            exists = true;
        }
    }
    return exists;
}
template bool Helper::existence_checker<std::string>(const string&, unordered_map<string,bool>&);
template bool Helper::existence_checker<std::vector<std::string>>(const vector<string>&, unordered_map<string,bool>&);

// Función miembro: ignored_file_checker(). 
// Permite validar la existencia del archivo en la lista de archivos ignorados.
bool Helper::ignored_file_checker(const string& file, const string& target_file) {
    bool is_ignored = false;
    // Se extraen los nombres de todos los archivos registrados en la lista de archivos ignorados en un vector
    vector<string> ignored_rows;
    rows_extractor(ignored_rows, target_file);
    // Recorremos los archivos ignorados para hacer las comparaciones respectivas
    for (const auto& ignored_item : ignored_rows) {
        // creamos un sub-string recortando el nombre del archivo por procesar de acuerdo al tamano del nombre del archivo ignorado
        string ignored_folder = file.substr(0, ignored_item.size());
        // Validamos que tanto los archivos como los directorios no se encuentren en la lista de archivos ignorados
        if (file == ignored_item || ignored_folder == ignored_item) {
            is_ignored = true;
        }
    }
    return is_ignored;
}

/*
 * Generators
 */

// Función miembro: location_generator(). 
// Contruye la ruta completa de un archivo en base a la ruta absoluta (ruta actual) y la ruta relativa del archivo (incluyendo el nombre del archivo) 
string Helper::location_generator(const string& file, const string& absolute_path) {
    string file_location = absolute_path + "/" + file;
    return file_location;
}

unsigned int Helper::hash_generator(const string& target_container, int mode) {
    unsigned int hash_value = 0;

    if (mode == action_mode::recursive) {
        ifstream target_container_istrm(target_container, std::ios::in | std::ios::binary);
        target_container_istrm.exceptions(ifstream::failbit | ifstream::badbit);

        string argumentfile_data_container {
            std::istreambuf_iterator<char>(target_container_istrm),
                std::istreambuf_iterator<char>()
        };
        target_container_istrm.close();
        target_container_istrm.clear();

        hash_value = std::hash<string> {}(argumentfile_data_container);
    } else if (mode == action_mode::simple) {
        hash_value = std::hash<string> {}(target_container);
    }

    return hash_value;
}

void Helper::timepoint_generator(string& timepoint) {
    auto current_timepoint = std::chrono::system_clock::now();
    std::time_t formated_timepoint = std::chrono::system_clock::to_time_t(current_timepoint);
    char formated_timepoint_buffer[20];
    strftime(formated_timepoint_buffer, sizeof(formated_timepoint_buffer), "%H:%M:%S %d-%m-%Y", localtime(&formated_timepoint));
    timepoint = formated_timepoint_buffer;
}

/*void Helper::compound_name_generator(const string& prefix, vector<string>& items) {
  for (auto& item : items) {
  item = prefix + "_" + item;
  } 
  }*/

/*
 * Organizers
 */

/*void Helper::data_organizer(File& data, const string& file, const string& target_folder) {
    data.file = file;
    data.file_hash = hash_generator(data.file, action_mode::recursive);
    data.file_name = fs::path(data.file).filename().string();
    data.file_extension = fs::path(data.file).extension().string();
    data.file_path = fs::path(data.file).parent_path().string();
    data.file_path_hash = std::hash<string> {}(data.file_path);
    data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name + data.file_extension;
    data.version = target_folder + "/" + data.version_name;
}*/

// Función miembro: data_organizer(). 
// Permite inicializar y llenar una estructura con los datos que necesita la versión de un archivo para ser capturada o guardada 
template<typename T, typename U>
void Helper::data_organizer(T& data_container, const U& rows, const string& target_folder, int mode) {
    // Capturamos la fecha y hora en la que se hizo la llamada al comando necesario para la captura o registro de la(s) versión(es)
    string temporal_date;
    timepoint_generator(temporal_date);

    // Llenamos la estructura de acuerdo al contenedor recibido
    if constexpr (std::is_same_v<T,File>) {
        // Para este tipo de contenedor y tomando en cuenta que (... ACA ME QUEDE)
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        // (ACA) Lo que falta es mejorar los nombres de los parametros de esta función para que sea más claro
        data_container.file = rows;
        // Generamos el valor hash del archivo
        // El modo "recursive" indica al método que el valor hash debe ser generado en base al contenido del archivo
        data_container.file_hash = hash_generator(data_container.file, action_mode::recursive);
        data_container.file_name = fs::path(data_container.file).filename().string();
        data_container.file_extension = fs::path(data_container.file).extension().string();
        data_container.file_path = fs::path(data_container.file).parent_path().string();
        // Generamos el valor hash de la ruta del archivo
        // El modo "simple" indica al método que el valor hash debe ser generado en base al nombre literal de la ruta 
        //data_container.file_path_hash = std::hash<string> {}(data_container.file_path);
        data_container.file_path_hash = hash_generator(data_container.file_path, action_mode::simple);
        data_container.version_name = std::to_string(data_container.file_path_hash) + "-" + std::to_string(data_container.file_hash) + "-" + data_container.file_name;
        data_container.version = target_folder + "/" + data_container.version_name;
        data_container.catch_date = temporal_date;
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);

            File data;
            data.file = items.at(db_pos::file);
            data.file_name = items.at(db_pos::file_name);
            data.file_extension = items.at(db_pos::file_extension);
            data.file_path = items.at(db_pos::path_name);
            data.file_path_hash = std::stoul(items.at(db_pos::path_hash));

            if (mode == action_mode::built) {
                data.file_hash = std::stoul(items.at(db_pos::file_hash));
                data.version_name = items.at(db_pos::version_name);
                data.version = items.at(db_pos::version);
                data.catch_date = items.at(db_pos::catch_date);
            } else if (mode == action_mode::to_build) {
                data.file_hash = hash_generator(data.file, action_mode::recursive);
                data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name;
                data.version = target_folder + "/" + data.version_name;
                data.catch_date = temporal_date;
            }
            data_container.push_back(data);
        }

    }

}
template void Helper::data_organizer<File,string>(File&, const string&, const string&, int);
template void Helper::data_organizer<vector<File>,vector<string>>(vector<File>&, const vector<string>&, const string&, int);


template<typename T> 
void Helper::data_organizer(vector<File>& data_container, const T& files, const string& target_folder) {
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& file : files) {
        File data;
        if constexpr (std::is_same_v<T,unordered_map<string,string>>) {
            data.file = file.second;
        } else if constexpr (std::is_same_v<T,vector<string>>) {
            data.file = file;
        }
        data.file_hash = hash_generator(data.file, action_mode::recursive);
        data.file_name = fs::path(data.file).filename().string();
        data.file_extension = fs::path(data.file).extension().string();
        data.file_path = fs::path(data.file).parent_path().string();
        //data.file_path_hash = std::hash<string> {}(data.file_path);
        data.file_path_hash = hash_generator(data.file_path, action_mode::simple);
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name;
        data.version = target_folder + "/" + data.version_name;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}
template void Helper::data_organizer<std::unordered_map<std::string,std::string>>(vector<File>&, const unordered_map<string,string>&, const string&);
template void Helper::data_organizer<std::vector<std::string>>(vector<File>&, const vector<string>&, const string&); // Hasta ahora solo usado en return


/* guardando
   void Helper::data_organizer(vector<File>& data_container, const vector<string>& rows, const string& target_folder, int mode) {
   string temporal_date;
   timepoint_generator(temporal_date);

   for (const auto& row : rows) {
   vector<string> items;
   items_extractor(items, row);

   File data;
   data.file = items.at(db_pos::file);
   data.file_name = items.at(db_pos::file_name);
   data.file_extension = items.at(db_pos::file_extension);
   data.file_path = items.at(db_pos::path_name);
   data.file_path_hash = std::stoul(items.at(db_pos::path_hash));

   if (mode == action_mode::built) {
   data.file_hash = std::stoul(items.at(db_pos::file_hash));
   data.version_name = items.at(db_pos::version_name);
   data.version = items.at(db_pos::version);
   data.catch_date = items.at(db_pos::catch_date);
   } else if (mode == action_mode::to_build) {
   data.file_hash = hash_generator(data.file, action_mode::recursive);
   data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name + data.file_extension;
   data.version = target_folder + "/" + data.version_name;
   data.catch_date = temporal_date;
   }
   data_container.push_back(data);
   }
   }*/


/*template<typename T>
  void Helper::data_organizer(T& data_container, ) {

  }*/

// REVISAR LOGICA DE ESTAS DOS FUNCIONES A DETALLE PARA VER SI PUEDEN UNIFICARSE
void Helper::availability_organizer(unordered_map<string,string>& available_files, const vector<string>& rows, const string& current_path) {
    for (const auto& file_or_folder : fs::recursive_directory_iterator(current_path)) {
        if (!fs::is_directory(file_or_folder)) {
            unsigned int temp_counter = 0;
            string formatted_file = file_or_folder.path().string();
            for (auto& ignored_file_or_folder : rows) {
                string comparison_file = formatted_file.substr(0, ignored_file_or_folder.size());
                if (ignored_file_or_folder != comparison_file) { 
                    temp_counter++; 
                } else {
                }
            }

            unsigned int temporal_hash = 0;
            if (temp_counter == rows.size()) {
                temporal_hash = hash_generator(formatted_file, action_mode::recursive);
                available_files.insert(make_pair(std::to_string(temporal_hash), formatted_file));
            }
        }
    }
}

// ESTE AVAILABLE PUEDE ESPERAR ANTES DE SER UBIDO A SU HERMANO DE ARRIBA DEBIDO A QUE AUN NO ESTAMOS EN "RETURN":w
void Helper::availability_organizer(vector<string>& available_files, vector<string>& available_folders, const vector<string>& rows, const string& current_path) {
    for (const auto& file_or_folder : fs::recursive_directory_iterator(current_path)) {
        unsigned int temp_counter = 0;
        string formatted_file = file_or_folder.path().string();
        for (auto& ignored_file_or_folder : rows) {
            string comparison_file = formatted_file.substr(0, ignored_file_or_folder.size());

            if (ignored_file_or_folder != comparison_file) { temp_counter++; } 
        }

        if (temp_counter == rows.size()) {
            if (fs::is_directory(formatted_file)) { available_folders.push_back(formatted_file); } 
            else { available_files.push_back(formatted_file); }
        } 
    }
}

void Helper::status_organizer(unordered_map<string,string>& untracked_files, unordered_map<string,string>& modified_files, unordered_map<string,string>& saved_files, const string& target_file) {
    string trimmed_target_file = target_file.substr(target_file.size() - db_catch.size(), db_catch.size());
    vector<string> rows;
    rows_extractor(rows, target_file);

    unordered_map<string,string> temporal_files;
    if (trimmed_target_file == db_catch) {
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
            temporal_files.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
        }
    } else {
        unordered_map<string,string> latest_version_checker;
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
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
        for (const auto& saved_file : saved_files) {
            untracked_files.erase(saved_file.first);
        }
    }

    if (hash_match_counter > 0) {
        for (const auto& modified_file : modified_files) {
            untracked_files.erase(modified_file.first);
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
            saved_not_modified.push_back(temp_saved_not_modified);
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


void Helper::duplicate_organizer(vector<string>& items) {
    std::sort(items.begin(), items.end());
    items.erase(std::unique(items.begin(), items.end()), items.end());
}

Helper::~Helper() {}
