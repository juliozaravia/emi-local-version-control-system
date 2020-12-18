/*
 * Project: EMI Personal Control Version System 
 * File: Builder Class - Implementation file
 * Description: Execution class. It allows us to perform the main actions such as 
 * creation, registration and deletion of directories and / or files among other actions.
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>

#include "../include/Builder.h"
#include "../include/Helper.h"
#include "../include/Communicator.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::endl;
using std::vector;
using std::unordered_map;
using std::ofstream;
using std::stringstream;

namespace fs = std::filesystem;

Builder::Builder() {
}
Builder::Builder(Base base)
    : base{base} {
    }

/*
 * Builders
 */

// Description: It allows us to build the repository that will contain the captured or saved versions, 
// the databases of the captured and saved versions and the configuration files in general.
void Builder::repository_builder(const string& current_path) {
    // We create the directory structure.
    fs::create_directory(base.emi_default_path);
    fs::create_directory(base.db_default_path);
    fs::create_directory(base.version_default_path);
    fs::create_directory(base.config_default_path);
    fs::create_directory(base.version_catch_path);
    fs::create_directory(base.version_main_path);
    fs::create_directory(base.version_temp_path);
    // We create the databases.
    ofstream db_catch_ostrm(base.db_catch_file, std::ios::out | std::ios::binary);
    db_catch_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_catch_ostrm.close();
    ofstream db_main_ostrm(base.db_main_file, std::ios::out | std::ios::binary);
    db_main_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_main_ostrm.close();
    ofstream db_temp_ostrm(base.db_temp_file, std::ios::out | std::ios::binary);
    db_temp_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_temp_ostrm.close();
    // We create the configuration files.
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

// Description: It allows us to create directories.
// The type of container received indicates the type of directory creation: single or multiple.
template <typename T>
void Builder::directory_builder(const T& directory_container) {
    if constexpr (std::is_same_v<T,string>) {
        fs::create_directory(directory_container);
    } else if constexpr (std::is_same_v<T,unordered_map<string,bool>>) {
        for (const auto& directory : directory_container) {
            if (!directory.second) {
                fs::create_directories(directory.first);
            }
        }
    }
}
template void Builder::directory_builder<string>(const string&);
template void Builder::directory_builder<unordered_map<string,bool>>(const unordered_map<string,bool>&);

/*
 * Cleaners
 */

// Description: It allows us to clean the data registered in a file.
void Builder::data_cleaner(const string& target_file) {
    // We open the stream associated with the target file.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::trunc);
    // We set the exception mask of the stream.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // We close and clean the stream.
    target_file_ostrm.close();
    target_file_ostrm.clear();
}

/*
 * Catchers & Savers
 */

// Description: It allows us to capture the version (data that make up the state and content) of an individual file or group of files.
template <typename T>
void Builder::data_catcher(const T& data_container, const string& target_file) {
    // We open the stream associated with the target file.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // We set the exception mask of the stream.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // The container type indicates whether an individual version or a group of versions will be captured.
    // Each of the data that makes up the structure of the version of a file is captured.
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
            << data_container.snap_version << ","
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
                << data.snap_version << ","
                << data.snap_date << ","
                << data.comment
                << endl;
        }
    }
    // We close and clean the stream.
    target_file_ostrm.close();
    target_file_ostrm.clear();
}
template void Builder::data_catcher<File>(const File&, const string&);
template void Builder::data_catcher<vector<File>>(const vector<File>&, const string&);

// Description: It allows us to save the version (data that make up the state and content) of an individual file or group of files.
void Builder::data_saver(const vector<string>& rows, const string& target_file, const string& timepoint, const string& timepoint_hash, const string& comment) {
    // We open the stream associated with the target file.
    ofstream db_main_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // We set the exception mask of the stream.
    db_main_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // We go through each of the rows extracted from the database of captured versions.
    for (const auto& row : rows) {
        string version_name;
        // We pass the extracted row to a stringstream.
        stringstream row_strm(row);

        unsigned int temp_counter = 0;
        while (std::getline(row_strm, version_name, ',')) {
            // When we get to the item corresponding to the version name (physical name of the file saved as version) we break the loop.
            // In this way the temporary variable 'version_name' will contain the name of the version we need.
            if (temp_counter == db_pos::version_name) { break; }
            temp_counter++;
        }
        // 'We trim' the extracted row in such a way that we save the data stored in the version capture phase.
        // Only empty values (null) that will be filled later will be excluded from the row.
        string trimmed_row = row.substr(0, row.size() - 17);
        // We build the path where the version of the file will be saved.
        // Note that all files will be registered in a folder. In this way we make sure that they are also physically grouped.
        string main_version_name = base.version_main_path + "/" + timepoint_hash + "/" + version_name; 
        // We register the necessary data in the database of saved versions.
        // Note that the variable 'trimmed_row' that was previously extracted is also being registered.
        db_main_file_ostrm << trimmed_row << ","
            << timepoint_hash << ","
            << main_version_name << ","
            << timepoint << ","
            << comment << endl;
    }
    // We close and clean the stream.
    db_main_file_ostrm.close();
    db_main_file_ostrm.clear();
}

/*
 * Inserters
 */

// Description: It allows us to insert one or more records into a file (generally a version database).
template <typename T>
void Builder::data_inserter(const T& row_or_rows, const string& target_file) {
    // We open the stream associated with the target file.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // We set the exception mask of the stream.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // We insert one or more records according to the type of container received.
    if constexpr (std::is_same_v<T,string>) {
        target_file_ostrm << row_or_rows << endl;
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& row : row_or_rows) {
            target_file_ostrm << row << endl;
        }
    }
    // We close and clean the stream.
    target_file_ostrm.close();
    target_file_ostrm.clear();
}
template void Builder::data_inserter<string>(const string&, const string&);
template void Builder::data_inserter<vector<string>>(const vector<string>&, const string&);

/*
 * Removers
 */

// Description: It allows us to delete a directory or several directories (recursively).
void Builder::repository_remover(const string& target_folder, int mode) {
    // Depending on the received mode, we can delete a directory in a standard way or we can delete the directory recursively 
    // (delete the directory and its contents recursively).
    if (mode == action_mode::simple) {
        fs::remove(target_folder);
    } else if (mode == action_mode::recursive) {
        fs::remove_all(target_folder);
    }
}

// Description: It allows us to remove an individual file or a group of files.
template <typename T>
void Builder::file_remover(const T& file_container, int data_identifier) {
    // We delete one or more files according to the type of container received.
    if constexpr (std::is_same_v<T,string>) {
        fs::remove(file_container);
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& item : file_container) {
            fs::remove(item);
        }
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        string file_to_remove;
        for (auto& data : file_container) {
            // In this case, the assignment of a 'data_identifier' tells us if we should delete the current file or its last stored version.
            if (data_identifier == db_pos::file) {
                file_to_remove = data.file;    
            } else if (data_identifier == db_pos::version) {
                file_to_remove = data.version;
            }
            fs::remove(file_to_remove);
        }
    } else if constexpr (std::is_same_v<T,unordered_map<string,bool>>) {
        for (auto& file : file_container) {
            if (file.second) {
                fs::remove(file.first);
            } 
        }
    }
}
template void Builder::file_remover<string>(const string&, int);
template void Builder::file_remover<vector<string>>(const vector<string>&, int);
template void Builder::file_remover<vector<File>>(const vector<File>&, int);
template void Builder::file_remover<unordered_map<string,bool>>(const unordered_map<string,bool>&, int);

/*
 * Transportes
 */

// Description: It allows us to move copies of files from one directory to another.
template<typename T>
void Builder::file_transporter(const T& data_container, const string& target_folder, const string& target_sub_folder) {
    string original_file;
    string temporal_file;
    // Depending on the type of container we can copy an individual file or multiple files.
    if constexpr (std::is_same_v<T,File>) {
        original_file = data_container.file;
        // We build the path where we will send the copy of the file.
        temporal_file = target_folder + "/" + data_container.version_name;
        // We copy the file from its original path to its final path.
        fs::copy_file(original_file, temporal_file);
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (const auto& data : data_container) {
            original_file = data.file;
            // We build the path where we will send the copy of the file.
            temporal_file = target_folder + "/" + data.version_name;
            // We copy the file from its original path to its final path.
            fs::copy_file(original_file, temporal_file);
        }
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        // The path of the subdirectory within the destination directory is defined.
        // This special case applies when the variable 'target_sub_folder' has content assigned.
        string temporal_path = target_folder + "/" + target_sub_folder; 
        // The subdirectory is created.
        fs::create_directory(temporal_path);

        for (const auto& original_file : data_container) {
            string version_name = fs::path(original_file).filename().string();
            temporal_file = temporal_path + "/" + version_name;
            // We copy the file from its original path to its final path.
            fs::copy_file(original_file, temporal_file);
        }  
    }
}
template void Builder::file_transporter<File>(const File&, const string&, const string&);
template void Builder::file_transporter<vector<File>>(const vector<File>&, const string&, const string&);
template void Builder::file_transporter<vector<string>>(const vector<string>&, const string&, const string&);

// Description: It allows us to move copies of files from one directory to another.
// This method has been built for the specific case required in the 'Manager: get_manager ()' method.
void Builder::special_transporter(const vector<string>& original_files, const vector<string>& final_files) {
    for (unsigned int i = 0; i < original_files.size(); i++) {
        fs::copy_file(original_files.at(i), final_files.at(i));
    }
}

/*
 * Others
 */

// Description: It allows us to change the name (rename) of a file or directory.
void Builder::file_renamer(const string& selected_name, const string& target_folder, const string& target_sub_folder) {
    string temporal_path_name = target_folder + "/" + target_sub_folder;
    string final_path_name = target_folder + "/" + selected_name;
    fs::rename(temporal_path_name, final_path_name);
}

Builder::~Builder() {}
