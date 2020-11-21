#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <iostream>

#include "../include/Builder.h"
#include "../include/Helper.h"
#include "../include/Communicator.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::endl;
using std::vector;
using std::ofstream;

namespace fs = std::filesystem;

Builder::Builder() {
}
Builder::Builder(Base base)
    : base{base} {
    }

/*
 * Builders
 */

void Builder::repository_builder(const string& current_path) {
    fs::create_directory(base.emi_default_path);
    fs::create_directory(base.db_default_path);
    fs::create_directory(base.version_default_path);
    fs::create_directory(base.config_default_path);
    fs::create_directory(base.version_catch_path);
    fs::create_directory(base.version_main_path);
    fs::create_directory(base.version_temp_path);

    ofstream db_catch_ostrm(base.db_catch_file, std::ios::out | std::ios::binary);
    db_catch_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_catch_ostrm.close();
    ofstream db_main_ostrm(base.db_main_file, std::ios::out | std::ios::binary);
    db_main_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_main_ostrm.close();
    ofstream db_temp_ostrm(base.db_temp_file, std::ios::out | std::ios::binary);
    db_temp_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_temp_ostrm.close();

    ofstream config_main_ostrm(base.config_main_file, std::ios::out | std::ios::binary);
    config_main_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    config_main_ostrm << std::hash<string> {}(base.emi_default_path) << endl;
    config_main_ostrm << current_path << endl;
    config_main_ostrm.close();
    ofstream config_ignore_ostrm(base.config_ignore_file, std::ios::out | std::ios::binary);
    config_ignore_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    config_ignore_ostrm << current_path + "/" + emi_path << endl;
    config_ignore_ostrm.close();
}

/*
 * Cleaners
 */

template <typename T>
void Builder::file_remover(const T& items_or_data, int data_identifier) {
    if constexpr (std::is_same_v<T,string>) {
        fs::remove(items_or_data);
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& item : items_or_data) {
            std::cout << "item para borrar -> " << item << std::endl;
            fs::remove(item);
        }
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        string file_to_remove;
        for (auto& data : items_or_data) {
            if (data_identifier == db_pos::file) {
                file_to_remove = data.file;    
            } else if (data_identifier == db_pos::version) {
                file_to_remove = data.version;
            }
            std::cout << "Va a remover el file -> " << file_to_remove << std::endl;
            fs::remove(file_to_remove);
        }
    }
}
template void Builder::file_remover<string>(const string&, int);
template void Builder::file_remover<vector<string>>(const vector<string>&, int);
template void Builder::file_remover<vector<File>>(const vector<File>&, int);

// EL nombre posiblemente esté mal ya que no remueve solo los folders sino que hace más operaciones
void Builder::folder_remover(vector<string>& folders) {
    std::sort(folders.begin(), folders.end(), [](const std::string& first, const std::string& second){
            return first.size() > second.size();});

    for (const auto& folder : folders) {
        unsigned int temp_counter = 0;
        for (const auto& file_or_folder : fs::recursive_directory_iterator(folder)) {
            if (!fs::is_directory(file_or_folder)) {
                temp_counter++;
            } 
        }

        if (temp_counter == 0) {
            std::cout << "Va a remover el folder -> " << folder << std::endl;
            fs::remove_all(folder);
            temp_counter = 0;
        }
    }
}

void Builder::data_cleaner(const string& target_file) {
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::trunc);
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    target_file_ostrm.close();
    target_file_ostrm.clear();
}

template <typename T>
void Builder::data_inserter(const T& row_or_rows, const string& target_file) {
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    if constexpr (std::is_same_v<T,string>) {
        target_file_ostrm << row_or_rows << endl;
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& row : row_or_rows) {
            target_file_ostrm << row << endl;
        }
    }

    target_file_ostrm.close();
    target_file_ostrm.clear();
}

template void Builder::data_inserter<string>(const string&, const string&);
template void Builder::data_inserter<vector<string>>(const vector<string>&, const string&);

/*
 * Catchers
 */

template <typename T>
void Builder::data_catcher(const T& data_container, const string& target_file) {
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    if constexpr (std::is_same_v<T,File>) {
        target_file_ostrm << data_container.file << ","
            << data_container.file_hash << ","
            << data_container.file_path << ","
            << data_container.file_path_hash << ","
            << data_container.version << ","
            << data_container.version_name << ","
            << data_container.file_name << ","
            << data_container.file_extension << ","
            << data_container.catch_date << ","
            << data_container.snap_hash << ","
            << data_container.snap_date << ","
            << data_container.comment
            << endl;
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (auto data : data_container) {
            target_file_ostrm << data.file << ","
                << data.file_hash << ","
                << data.file_path << ","
                << data.file_path_hash << ","
                << data.version << ","
                << data.version_name << ","
                << data.file_name << ","
                << data.file_extension << ","
                << data.catch_date << ","
                << data.snap_hash << ","
                << data.snap_date << ","
                << data.comment
                << endl;
        }
    }

    target_file_ostrm.close();
    target_file_ostrm.clear();
}
template void Builder::data_catcher<File>(const File&, const string&);
template void Builder::data_catcher<vector<File>>(const vector<File>&, const string&);

/*
 * Savers
 */

void Builder::file_renamer(const string& selected_name, const string& target_folder, const string& target_sub_folder) {
    string temporal_path_name = target_folder + "/" + target_sub_folder;
    string final_path_name = target_folder + "/" + selected_name;
    fs::rename(temporal_path_name, final_path_name);
}

void Builder::data_saver(const vector<string>& rows, const string& target_file, const string& timepoint, const string& comment) {
    ofstream db_main_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    db_main_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    unsigned int timepoint_hash = std::hash<string> {}(timepoint);
    for (const auto& row : rows) {
        string trimmed_row = row.substr(0, row.size() - 12);
        db_main_file_ostrm << trimmed_row << ","
            << timepoint_hash << ","
            << timepoint << ","
            << comment << endl;
    }

    db_main_file_ostrm.close();
    db_main_file_ostrm.clear();
}

/*
 * Removers
 */

void Builder::repository_remover(const string& target_folder, int mode) {
    if (mode == action_mode::simple) {
        fs::remove(target_folder);
    } else if (mode == action_mode::recursive) {
        fs::remove_all(target_folder);
    }
}

template<typename T>
void Builder::file_transporter(const T& data_container, const string& target_folder, const string& target_sub_folder) {
    string original_file;
    string temporal_file;

    if constexpr (std::is_same_v<T,File>) {
        original_file = data_container.file;
        temporal_file = target_folder + "/" + data_container.version_name;
        fs::copy_file(original_file, temporal_file);
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (const auto& data : data_container) {
            original_file = data.file;
            temporal_file = target_folder + "/" + data.version_name;
            std::cout << "Va a mover de aca -> " << original_file << " hacia acá -> " << temporal_file << std::endl;
            fs::copy_file(original_file, temporal_file);
        }
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        string temporal_path = target_folder + "/" + target_sub_folder; 
        fs::create_directory(temporal_path);

        for (const auto& original_file : data_container) {
            string version_name = fs::path(original_file).filename().string();
            temporal_file = temporal_path + "/" + version_name;
            fs::copy_file(original_file, temporal_file);
        }  
    }
}

template void Builder::file_transporter<File>(const File&, const string&, const string&);
template void Builder::file_transporter<vector<File>>(const vector<File>&, const string&, const string&);
template void Builder::file_transporter<vector<string>>(const vector<string>&, const string&, const string&);

Builder::~Builder() {}
