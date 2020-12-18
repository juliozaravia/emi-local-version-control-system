/*
 * Project: EMI Personal Control Version System 
 * File: Helper Class - Implementation file
 * Description: Operations support class. It allows us to carry out complementary and support actions 
 * for the main actions such as creating, registering and deleting directories and / or files, among other actions.
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

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

// Description: It allows us to compare 2 text strings, returning the value of true if they are the same or false if they are different.
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

// Description: It allows us to extract data (rows of data) from a file and store it in a container according to the complementary parameters.
void Helper::rows_extractor(vector<string>& rows, const string& target_file, const string& comparison_row, int mode, int item_position) {
    // We open the stream associated with the target file.
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    // We set the exception mask of the stream.
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);
    // The operations branch according to the complementary parameters.
    try {
        string target_file_row;
        if (comparison_row.empty()) {
            // We extract line by line all the data from the file and store it in a container.
            while (std::getline(target_file_istrm, target_file_row)) {
                rows.push_back(target_file_row);
            }
        } else {
            if (mode == action_mode::different_to_row) {
                // We extract all the data from the file line by line, excluding the row corresponding to the comparison string.
                while (std::getline(target_file_istrm, target_file_row)) {
                    if (target_file_row != comparison_row) {
                        rows.push_back(target_file_row);
                    }
                }
            } else if (mode == action_mode::similar_to_item) {
                // We extract all rows of data from the file as long as the extracted row matches the comparison string.
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
    // We close and clean the stream.
    target_file_istrm.close();
    target_file_istrm.clear();
}

// Description: It allows us to search and extract the row of data from the target file that matches the name of the received file.
string Helper::row_extractor(const string& file, const string& target_file) {
    string extracted_row;
    vector<string> rows;
    // We use the 'rows_extractor' method to fill all the rows of the target file into a container.
    rows_extractor(rows, target_file);

    for (const auto& row : rows) {
        // We extract the name of the file from the extracted row.
        string trimmed_file = row.substr(0, file.size());
        // We compare the name of the received file with the name of the extracted file.
        // If they match, the loop ends and the found value is returned.
        if (file == trimmed_file) {
            extracted_row = row;
            break;
        }
    }
    return extracted_row;
}

// Description: It allows us to extract the items from a text string. The separator character must be specified.
void Helper::items_extractor(vector<string>& items, const string& row, char separator) {
    string row_item;
    // We pass the received text string to a stringstream.
    stringstream row_strm(row);
    // We go through the stream and capture each item in a variable.
    // We store each of the extracted values in a container.
    while (std::getline(row_strm, row_item, separator)) {
        items.push_back(row_item);
    }
}

// Description: We extract specific data from a file or container.
template<typename T, typename U>
void Helper::content_extractor(T& item_or_items, const U& target_container, int item_position) {
    // The container that will receive the data is a text string.
    // This means that the value to be stored is individual.
    if constexpr (std::is_same_v<T,string>) {
        vector<string> extracted_items;
        // We use the 'items_extractor' method to extract all items from the target file.
        // We use the received position value to specifically extract the value of the item at that position.
        // We store the extracted item in the container.
        items_extractor(extracted_items, target_container);
        item_or_items = extracted_items.at(item_position);
        // The container that will receive the data is a multiple storage container. In this case a vector.
        // This means that it will serve to store several items.
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        vector<string> rows;
        // The container from which we will extract the data is a text string.
        // This means that this text string refers to a file name.
        if constexpr (std::is_same_v<U,string>) {
            // We extract all the rows from the target file and store it in a container.
            rows_extractor(rows, target_container);
            // The container from which we will extract the data is a multiple storage container.
            // This means that the necessary rows have already been extracted previously.
        } else if constexpr (std::is_same_v<U,vector<string>>) {
            rows = target_container;    
        }

        for (const auto& row : rows) {
            vector<string> extracted_items;
            // We extract all the items from each of the rows of the container.
            // We use the received position value to specifically extract the value of the item at that position.
            // We store the extracted item in the container.
            items_extractor(extracted_items, row);
            item_or_items.push_back(extracted_items.at(item_position));
        }
    }
}
template void Helper::content_extractor<string, string>(string&, const string&, int);
template void Helper::content_extractor<vector<string>,string>(vector<string>&, const string&, int);
template void Helper::content_extractor<vector<string>,vector<string>>(vector<string>&, const vector<string>&, int);

/*
 * Checkers
 */

// Description: It allows us to check if a file has content or is empty.
bool Helper::content_checker(const string& target_file) {
    // We open the stream associated with the target file.
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    // We set the exception mask of the stream.
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    bool file_has_data = true;
    // We take a 'look' at the file to determine if we are reaching EOF.
    if (target_file_istrm.peek() == ifstream::traits_type::eof()) { file_has_data = false; }
    // We close and clean the stream.
    target_file_istrm.close();
    target_file_istrm.clear();

    return file_has_data;
}

// Description: It allows us to verify if a file or group of files exist or not and return its status.
template <typename T>
bool Helper::existence_checker(const T& file_or_files, unordered_map<string,bool>& status) { 
    bool exists = false;
    // The file container is a text string.
    // This means that we want to verify the existence of an individual file.
    if constexpr (std::is_same_v<T,string>) {
        if (fs::exists(file_or_files)) {
            exists = true;
        }
    // The file container is a multiple storage container.
    // This means that we want to verify the existence of a group of files.
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        unsigned int temp_counter = 0;
        // We check the existence of each file.
        // If the file exists a counter is incremented.
        // The name of the file and its associated state are inserted into the state container true if it exists, false if it does not exist.
        for (const auto& file : file_or_files) {
            if (fs::exists(file)) {
                temp_counter++;
                status.insert(make_pair(file,true));
            } else {
                status.insert(make_pair(file,false));
            }
        }

        // If the counter is equal to the number of items in the container, all the files exist.
        if (temp_counter == file_or_files.size()) {
            exists = true;
        }
    }
    return exists;
}
template bool Helper::existence_checker<std::string>(const string&, unordered_map<string,bool>&);
template bool Helper::existence_checker<std::vector<std::string>>(const vector<string>&, unordered_map<string,bool>&);

// Description: It allows us to validate the existence of the file in the ignore list.
bool Helper::ignored_file_checker(const string& file, const string& target_file) {
    bool is_ignored = false;
    // The 'rows_extractor' method is used to extract the rows from the ignore file.
    // We must remember that the ignore file not only stores files but also paths.
    vector<string> ignored_rows;
    rows_extractor(ignored_rows, target_file);

    for (const auto& ignored_item : ignored_rows) {
        // We create a sub-string by trimming the name of the file to be processed.
        // This new item must be a directory.
        string ignored_folder = file.substr(0, ignored_item.size());
        // We validate that both the files and the directories are not in the ignore list.
        if (file == ignored_item || ignored_folder == ignored_item) {
            is_ignored = true;
        }
    }
    return is_ignored;
}

/*
 * Generators
 */

// It allows us to build the complete path of a file based on the absolute path (current path) and the relative path of the file.
string Helper::location_generator(const string& file, const string& absolute_path) {
    string file_location = absolute_path + "/" + file;
    return file_location;
}

// Description: It allows us to generate a hash value based on the content of a file or a simple text string.
unsigned int Helper::hash_generator(const string& target_container, int mode) {
    unsigned int hash_value = 0;
    // The data needs to be previously extracted from a file (action_mode::recursive).
    if (mode == action_mode::recursive) {
        // We open the stream associated with the target file.
        ifstream target_container_istrm(target_container, std::ios::in | std::ios::binary);
        // We set the exception mask of the stream.
        target_container_istrm.exceptions(ifstream::failbit | ifstream::badbit);
        // We store the extracted data in a container (buffer).
        string argumentfile_data_container {
            std::istreambuf_iterator<char>(target_container_istrm),
                std::istreambuf_iterator<char>()
        };
        // We close and clean the stream.
        target_container_istrm.close();
        target_container_istrm.clear();
        // We generate the hash value based on the content of the file.
        hash_value = std::hash<string> {}(argumentfile_data_container);
    // The data will be generated based on a text string.
    } else if (mode == action_mode::simple) {
        // We generate the hash value based on the text string.
        hash_value = std::hash<string> {}(target_container);
    }

    return hash_value;
}

// Description: It allows us to capture the exact moment in which an action is executed.
void Helper::timepoint_generator(string& timepoint) {
    // We capture the time of the internal clock of the computer in which the operation is being executed.
    auto current_timepoint = std::chrono::system_clock::now();
    // We apply the necessary format to execute the other operations.
    std::time_t formated_timepoint = std::chrono::system_clock::to_time_t(current_timepoint);
    char formated_timepoint_buffer[20];
    strftime(formated_timepoint_buffer, sizeof(formated_timepoint_buffer), "%H:%M:%S %d-%m-%Y", localtime(&formated_timepoint));
    timepoint = formated_timepoint_buffer;
}

/*
 * Organizers
 */

// Description: It allows us to fill in the structure of the necessary data that we must complete so that the version can be captured or saved correctly.
template<typename T, typename U>
void Helper::data_organizer(T& data_container, const U& rows, const string& target_folder, int mode) {
    // We capture the date and time in which the call to the necessary command was made to capture or save the version(s).
    string temporal_date;
    timepoint_generator(temporal_date);

    // The container 'data_container' allows to store a single data structure.
    if constexpr (std::is_same_v<T,File>) {
        // The 'rows' container brings the data that we must process to fill the structure, it is a text string.
        // This means that it is simply the path of the file to process.
        data_container.file = rows;
        // We fill in the data required by the structure: 
        // Full path of the file, hash value of the file, name of the file, extension of the file, 
        // path of the file without considering its name, hash value generated with the path of the file, 
        // name of the version of the file, full path of the file version, date and time captured when executing the operation.
        data_container.file_hash = hash_generator(data_container.file, action_mode::recursive);
        data_container.file_name = fs::path(data_container.file).filename().string();
        data_container.file_extension = fs::path(data_container.file).extension().string();
        data_container.file_path = fs::path(data_container.file).parent_path().string();
        data_container.file_path_hash = hash_generator(data_container.file_path, action_mode::simple);
        data_container.version_name = std::to_string(data_container.file_path_hash) + "-" + std::to_string(data_container.file_hash) + "-" + data_container.file_name;
        data_container.version = target_folder + "/" + data_container.version_name;
        data_container.catch_date = temporal_date;
    // The container 'data_container' allows to store multiple data structures.
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        // The 'rows' container brings the data that we must process to fill the structure, it is a multiple storage container.
        // This means that we must go through its content and process each item to fill each structure consecutively.
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
            File data;
            data.file = items.at(db_pos::file);
            data.file_name = items.at(db_pos::file_name);
            data.file_extension = items.at(db_pos::file_extension);
            data.file_path = items.at(db_pos::path_name);
            data.file_path_hash = std::stoul(items.at(db_pos::path_hash));
            // According to the assigned mode we can choose between extracting the data from the 'rows' container or generating it.
            // Extract the data registered in 'rows' indicates that the file being processed has not been modified later and its registered data is the most recent.
            if (mode == action_mode::built) {
                data.file_hash = std::stoul(items.at(db_pos::file_hash));
                data.version_name = items.at(db_pos::version_name);
                data.version = items.at(db_pos::version);
                data.catch_date = items.at(db_pos::catch_date);
            // Generate the data indicates that the file being processed has been subsequently modified and its registered data is not the most recent.
            // Therefore, we need to generate updated data to perform the operations.
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

// Description: It allows us to fill in the structure of the necessary data that we must complete so that the version can be captured or saved correctly.
template<typename T> 
void Helper::data_organizer(vector<File>& data_container, const T& files, const string& target_folder) {
    // We capture the date and time in which the call to the necessary command was made to capture or save the version(s).
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
        data.file_path_hash = hash_generator(data.file_path, action_mode::simple);
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name;
        data.version = target_folder + "/" + data.version_name;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}
template void Helper::data_organizer<std::unordered_map<std::string,std::string>>(vector<File>&, const unordered_map<string,string>&, const string&);
template void Helper::data_organizer<std::vector<std::string>>(vector<File>&, const vector<string>&, const string&);

// Description: It allows us to separate the files available to be processed from the files that are registered in the ignored file.
void Helper::availability_organizer(unordered_map<string,string>& available_files, const vector<string>& rows, const string& current_path) {
    // We go through all the files or folders that belong to the current path.
    for (const auto& file_or_folder : fs::recursive_directory_iterator(current_path)) {
        // We only allow operations to be performed on files.
        if (!fs::is_directory(file_or_folder)) {
            unsigned int temp_counter = 0;
            string formatted_file = file_or_folder.path().string();
            // We go through the container 'rows' that contains all the files registered in the ignored file.
            for (auto& ignored_file_or_folder : rows) {
                // We make the size of the 'formatted_file' match the size of the ignored file, so we can compare them.
                string comparison_file = formatted_file.substr(0, ignored_file_or_folder.size());
                // We compare both file names. If they are different, we increase the value of a temporary counter.
                if (ignored_file_or_folder != comparison_file) { 
                    temp_counter++; 
                } 
            }

            unsigned int temporal_hash = 0;
            // The number stored in the counter is equal to the number of items in the 'rows' container.
            // This means that the file being processed is not registered in the ignore list.
            if (temp_counter == rows.size()) {
                temporal_hash = hash_generator(formatted_file, action_mode::recursive);
                // We insert, in a structure of type unordered_map, the hash value generated with the content of the file as key; 
                // and, the name of the file as an associated value.
                available_files.insert(make_pair(std::to_string(temporal_hash), formatted_file));
            }
        }
    }
}

// Description: It allows us to group files according to their status: Not tracked, modified, captured or saved.
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

// Description: It allows us to organize the detailed information of the application of the -snapshot command.
// Information: Unique snapshot code, execution date and time, associated comment and saved files.
void Helper::log_organizer(Log& log, vector<Log>& log_info, unordered_multimap<string,string>& saved_files, const vector<string>& rows) {
    string temp_hash;
    string temp_date;
    string temp_comment;
    // We go through all the rows extracted from the database of saved versions.
    for (const auto& row : rows) {
        // We extract the items from each of the rows and store them in a container.
        vector<string> items;
        items_extractor(items, row);
        // We insert, in a structure of type unordered_map, the hash value of the snapshot as key; 
        // and, the name of the file as an associated value.
        saved_files.insert(make_pair(items.at(db_pos::snap_hash),items.at(db_pos::file)));
        // We extract the following values from the version group: hash value of the snapshot, date and time of saving the files.
        // and, the comment that the user writes regarding the action taken or the reason for saving files.
        if (temp_hash != items.at(db_pos::snap_hash)) {
            log.snapshot_code = items.at(db_pos::snap_hash);
            log.snapshot_date = items.at(db_pos::snap_date);
            log.snapshot_comment = items.at(db_pos::comment);
            log_info.push_back(log);
        }
        temp_hash = items.at(db_pos::snap_hash);
    }
}

// Description: It allows us to group files according to their status: 'saved and modified' and 'saved and not modified'.
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


// Description: It allows us to sort and eliminate duplicate items within a container.
void Helper::duplicate_organizer(vector<string>& items) {
    std::sort(items.begin(), items.end());
    items.erase(std::unique(items.begin(), items.end()), items.end());
}

Helper::~Helper() {}
