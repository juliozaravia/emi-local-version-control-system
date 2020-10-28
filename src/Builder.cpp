#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <type_traits>

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
    config_ignore_ostrm << emi_path << endl;
    config_ignore_ostrm.close();
}

/*
 * Cleaners
 */

template <typename T>
void Builder::file_remover(const T& items_or_data, const string& target_folder) {
//void Builder::file_remover(const vector<string>& items) {
    if constexpr (std::is_same_v<T,vector<string>>) {
        string file_to_remove = target_folder + "/" +
            items_or_data.at(db_pos::path_hash) + "-" +
            items_or_data.at(db_pos::file_hash) +
            items_or_data.at(db_pos::file_extension);
        fs::remove(file_to_remove);
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (auto& data : items_or_data) {
            string file_to_remove = target_folder + "/" +
                std::to_string(data.file_path_hash) + "-" +
                std::to_string(data.file_hash) +
                data.file_extension;
            fs::remove(file_to_remove);
        }
    }
}
template void Builder::file_remover<vector<string>>(const vector<string>&, const string&);
template void Builder::file_remover<vector<File>>(const vector<File>&, const string&);

void Builder::data_cleaner(const string& target_file) {
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::trunc);
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    target_file_ostrm.close();
    target_file_ostrm.clear();
}

template <typename T>
void Builder::data_inserter(const T& row_or_rows, const string& target_file) {
    //void Builder::data_inserter(const vector<string>& rows, const string& target_file) {
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
void Builder::data_catcher(const T& data_container, const string& target_file, const string& target_folder) {
    //void Builder::data_catcher(const vector<File>& data_container) {
    if constexpr (std::is_same_v<T,File>) {
        string version_file = target_folder + "/" + data_container.version_name;
        fs::copy_file(data_container.file, version_file);

        ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
        target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
        target_file_ostrm << data_container.file << ","
            << data_container.file_hash << ","
            << data_container.file_path << ","
            << data_container.file_path_hash << ","
            << data_container.version_name << ","
            << data_container.file_name << ","
            << data_container.file_extension << ","
            << data_container.catch_date << ","
            << data_container.snap_hash << ","
            << data_container.snap_date << ","
            << data_container.comment
            << endl;

        target_file_ostrm.close();
        target_file_ostrm.clear();
        // HACER PRUEBAS DE SACAT EL OPEN/CLOSE DEL OFSTREAM FUERA DEL IF
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (auto data : data_container) {
            string version_file = target_folder + "/" + data.version_name;
            fs::copy_file(data.file, version_file);

            ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
            target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
            target_file_ostrm << data.file << ","
                << data.file_hash << ","
                << data.file_path << ","
                << data.file_path_hash << ","
                << data.version_name << ","
                << data.file_name << ","
                << data.file_extension << ","
                << data.catch_date << ","
                << data.snap_hash << ","
                << data.snap_date << ","
                << data.comment
                << endl;

            target_file_ostrm.close();
            target_file_ostrm.clear();
        }
    }
}

template void Builder::data_catcher<File>(const File&, const string&, const string&);
template void Builder::data_catcher<vector<File>>(const vector<File>&, const string&, const string&);

/*
 * Savers
 */

void Builder::file_renamer(const string& timepoint, const string& target_folder, const string& target_sub_folder) {
    size_t timepoint_hash = std::hash<string> {}(timepoint);
    //string temp_version_directory = base.version_main_path + "/" + version_temp;
    string temporal_path_name = target_folder + "/" + target_sub_folder;
    string final_path_name = target_folder + "/" + std::to_string(timepoint_hash);
    fs::rename(temporal_path_name, final_path_name);
}

void Builder::data_saver(const vector<string>& rows, const string& target_file, const string& timepoint, const string& comment) {
    ofstream db_main_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    db_main_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);

    size_t timepoint_hash = std::hash<string> {}(timepoint);
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

void Builder::file_transporter(const vector<string>& files, const string& original_location, const string& target_folder, const string& target_sub_folder) {
    string temporal_location = target_folder + "/" + target_sub_folder;
    fs::create_directory(temporal_location);

    for (const auto& file : files) {
        string original_file = original_location + "/" + file;
        string temporal_file = temporal_location + "/" + file;

        fs::copy_file(original_file, temporal_file);
        fs::remove(original_file);
    }
}

/*
Momentaneamene comentado porque se creo en return este duplicao, nose si se mantendraaaaaaaaaaaaaaaaaaaaaaaaaaaaa
void Builder::version_transporter(const vector<File>& datas, const string& target_file) {
    for (auto data : datas) {
        string original_file = data.file;
        string temporal_file = target_file  + "/" + data.version_name;
        fs::copy_file(original_file, temporal_file);
        fs::remove(original_file);
    }
}*/

Builder::~Builder() {}
