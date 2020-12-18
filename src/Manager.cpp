/*
 * Project: EMI Personal Control Version System 
 * File: Manager Class - Implementation file
 * Description: Operations distribution class. It allows us to distribute and assign responsibilities between 
 * the support and execution methods to carry out the request made by the user.
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

#include "../include/Manager.h"
#include "../include/Builder.h"
#include "../include/Helper.h"
#include "../include/Communicator.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_multimap;

// We define and initialize the constructor.
// We build all the necessary paths that will be used by the Manager class and the execution and support classes.
// We use the "base" structure to store the paths.
Manager::Manager(string current_path, vector<string> arg_container)
    : current_path{current_path},
    arg_container{arg_container} {
        this->base.emi_default_path = current_path + "/" + emi_path;
        this->base.config_default_path = current_path + "/" + emi_path + "/" + config_path;
        this->base.db_default_path = current_path + "/" + emi_path + "/" + db_path;
        this->base.version_default_path = current_path + "/" + emi_path + "/" + version_path;
        this->base.config_main_file = current_path + "/" + emi_path + "/" + config_path + "/" + config_main;
        this->base.config_ignore_file = current_path + "/" + emi_path + "/" + config_path + "/" + config_ignore;
        this->base.db_catch_file = current_path + "/" + emi_path + "/" + db_path + "/" + db_catch;
        this->base.db_main_file = current_path + "/" + emi_path + "/" + db_path + "/" + db_main;
        this->base.db_temp_file = current_path + "/" + emi_path + "/" + db_path + "/" + db_temp;
        this->base.version_catch_path = current_path + "/" + emi_path + "/" + version_path + "/" + version_catch;
        this->base.version_main_path = current_path + "/" + emi_path + "/" + version_path + "/" + version_main;
        this->base.version_temp_path = current_path + "/" + emi_path + "/" + version_path + "/" + version_temp;
    }

// Member function: start_manager ().
// Invoked through the -start command.
// Ex: emi -start
void Manager::start_manager() {
    // We create (initialize) the "builder" object in order to create the emi repository.
    // Within the emi repository are the configurations, databases and files that will allow version tracking and storage.
    Builder builder(base);
    builder.repository_builder(current_path);
    Communicator printer;
    printer.event_reporter(success_codes::emi_repository_created);
}

// Member function: catch_manager (). Invoked through the -catch command.
// According to the parameters sent, it must be determined which of the sub-functions will be executed.
// Capture single file version: simple_catch_manager ().
// Capture the versions of multiple files: multiple_catch_manager ()
void Manager::catch_manager() {
    if (arg_container[2] == process_all) {
        multiple_catch_manager();
    } else {
        simple_catch_manager();
    }
}

// Member function: simple_catch_manager ().
// Invoked through the -catch command and assigning as an additional parameter the file whose version will be captured.
// Ex: emi -catch relative_folder/file.txt
void Manager::simple_catch_manager() {
    Communicator printer;
    Helper helper;
    // We build the full path of the file whose version will be captured.
    string file = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // We validate the existence of the file.
    bool file_exists = helper.existence_checker<string>(file, status);
    if (file_exists) {
        // We validate that the file is not registered in the list of ignored files.
        bool file_is_ignored = helper.ignored_file_checker(file, base.config_ignore_file);
        if (!file_is_ignored) {
            Builder builder;
            File data;
            // We build the structure and fill it with the necessary information generated (based on the file) to capture the most recent version of the file.
            helper.data_organizer<File,string>(data, file, base.version_catch_path);
            // We look for the file that will be processed in the database of captured versions.
            // This is done in order to determine if a version of the file has already been captured previously.
            string catch_row = helper.row_extractor(data.file, base.db_catch_file);
            if (catch_row.empty()) {
                // We look for the file that will be processed in the database of saved versions.
                // This is done in order to determine if a version of the file has already been saved previously.
                string main_row = helper.row_extractor(data.file, base.db_main_file);
                if (main_row.empty()) {
                    // We transport (copy and rename) the most recent version of the file to the directory of captured versions.
                    // We register the data of the most recent version of the file in the database of captured versions.
                    builder.file_transporter<File>(data, base.version_catch_path);
                    builder.data_catcher<File>(data, base.db_catch_file);
                    printer.event_reporter(success_codes::version_catched);
                } else {
                    string temporal_file_hash;
                    // We extract the record corresponding to the hash value of the version registered in the database of saved versions.
                    // We compare the hash value of the version stored in the database and the hash value of the current file version.
                    // We do this in order to determine if the file was modified after it was captured.
                    helper.content_extractor<string,string>(temporal_file_hash, main_row, db_pos::file_hash);
                    bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
                    if (is_same_hash) {
                        printer.warning_reporter(warning_codes::identical_version_saved);
                    } else {
                        // We transport (copy and rename) the most recent version of the file to the directory of captured versions.
                        // We register the data of the most recent version of the file in the database of captured versions.
                        builder.file_transporter<File>(data, base.version_catch_path);
                        builder.data_catcher<File>(data, base.db_catch_file);
                        printer.event_reporter(success_codes::version_catched);
                    }
                }
            } else {
                string temporal_file_hash;
                // We extract the record corresponding to the hash value of the version registered in the database of captured versions.
                // We compare the hash value of the version stored in the database and the hash value of the current file version.
                // We do this in order to determine if the file was modified after it was captured.
                helper.content_extractor<string,string>(temporal_file_hash, catch_row, db_pos::file_hash);
                bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
                if (is_same_hash) {
                    printer.warning_reporter(warning_codes::identical_version_in_standby);
                } else {
                    vector<string> protected_rows;
                    string temporal_version;
                    // We extract all the records (rows) from the captured versions database excluding the record (row) that corresponds to the file we're working with.
                    // We extract the record corresponding to the full name of the version registered in the database of captured versions.
                    helper.rows_extractor(protected_rows, base.db_catch_file, catch_row, action_mode::different_to_row);
                    helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                    // We remove the version found in the captured versions directory.
                    // We remove the records from the captured versions database.
                    // We insert the records previously extracted into the database of captured versions.
                    // We transport (copy and rename) the most recent version of the file to the directory of captured versions.
                    // We register the data of the most recent version of the file in the database of captured versions.
                    builder.file_remover<string>(temporal_version);
                    builder.data_cleaner(base.db_catch_file);
                    builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);
                    builder.file_transporter<File>(data, base.version_catch_path);
                    builder.data_catcher<File>(data, base.db_catch_file);
                    printer.event_reporter(success_codes::version_catched);
                }
            }
        } else {
            printer.warning_reporter(warning_codes::file_already_ignored, catch_command);
        }
    } else {
        printer.warning_reporter(warning_codes::file_not_found);
    }
}

// Member function: multiple_catch_manager ().
// Invoked through the -catch command and assigning the "all" subcommand as an additional parameter
// Ex. emi -catch all
void Manager::multiple_catch_manager() {
    // We create the necessary containers to store the information of:
    // (1) untracked_files: Files that do not yet have a version captured by the -catch command.
    // (2) modified_files: Files that differ from their most recent captured or saved version.
    // (3) standby_files: Files that have a captured version and at the same time placed in the standby stage using the -catch command.
    // (4) saved_files: Files that have a version saved using the -snapshot command.
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;

    Communicator printer;
    Helper helper;
    // We fill the container "untracked_files" only with the files that are not registered in the list of ignored files.
    // The hash value of the latest version of the file and the full path of the file will be saved.
    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // We validate that there are available files (that is, files that have not been ignored, captured or saved before).
    if (untracked_files.empty()) {
        printer.event_reporter(notification_codes::no_files_found, catch_command);
    } else {
        // We create the necessary containers to process the information:
        // (1) catched_modified: Files whose most recent version is different from the last captured version.
        // (2) catched_not_modified: Files whose most recent version is equal to their last captured version.
        // (3) saved_modified: Files whose most recent version is different from their last saved version.
        // (4) saved_not_modified: Files whose most recent version is equal to their last saved version.
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        vector<string> saved_modified;
        vector<string> saved_not_modified;
        // We create the containers that will be filled with the processed data of catched_modified, catched_not_modified, saved_modified and saved_not_modified.
        vector<File> old_data;
        vector<File> catched_modified_data;
        vector<File> saved_modified_data;
        vector<File> untracked_data;
        // We validate if the database of captured versions is empty or has records.
        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            // We fill the containers of type "unordered_map" with the respective information.
            // At this point we only process the data from the captured versions database.
            // The database of saved versions will be analyzed later.
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            // We fill the containers of type "vector" with the data processed and stored in modified_files and standby_files.
            helper.processed_files_organizer(catched_modified, catched_not_modified, modified_files, standby_files, base.db_catch_file);
            // We validate if the database of saved versions is empty or has records.
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // We fill the containers of type "unordered_map" with the respective information.
                // At this point we only process the data from the saved versions database.
                // The database of captured versions was previously analyzed so this activity completes the filling of the containers.
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                // We fill the containers of type "vector" with the data processed and stored in modified_files and saved_files.
                helper.processed_files_organizer(saved_modified, saved_not_modified, modified_files, saved_files, base.db_main_file);
                // We fill the previously declared structures as follows:
                // (1) old_data: Data of the files whose most recent version is different from the last captured version.
                // This data is extracted from the records of the captured version database (action_mode::built).
                // (2) catched_modified_data: Data of the files whose most recent version is different from the last captured version.
                // This data is built based on the new information in the file (action_mode::to_build).
                // (3) saved_modified_data: Data of the files whose latest version is different from the last saved version.
                // This data is built based on the new information in the file (action_mode::to_build).
                // (4) untracked_data: Data of the files that have not yet been captured or saved.
                helper.data_organizer<vector<File>,vector<string>>(old_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<vector<File>,vector<string>>(saved_modified_data, saved_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            } else {
                // We fill the previously declared structures as follows:
                // (1) old_data: Data of the files whose most recent version is different from the last captured version.
                // This data is extracted from the records of the captured version database (action_mode::built).
                // (2) catched_modified_data: Data of the files whose most recent version is different from the last captured version.
                // This data is built based on the new information in the file (action_mode::to_build).
                // (3) untracked_data: Data of the files that have not yet been captured or saved.
                helper.data_organizer<vector<File>,vector<string>>(old_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            }
        } else {
            // We validate if the database of saved versions is empty or has records.
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // We fill the containers of type "unordered_map" with the respective information.
                // At this point we only process the data from the saved versions database.
                // The database of captured versions was not analyzed because it is empty.
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                // We fill the containers of type "vector" with the data processed and stored in modified_files and saved_files.
                helper.processed_files_organizer(saved_modified, saved_not_modified, modified_files, saved_files, base.db_main_file);
                // We fill the previously declared structures as follows:
                // (1) saved_modified_data: Data of the files whose latest version is different from the last saved version.
                // This data is built based on the new information in the file (action_mode::to_build).
                // (2) untracked_data: Data of the files that have not yet been captured or saved.
                helper.data_organizer<vector<File>,vector<string>>(saved_modified_data, saved_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            } else {
                // We fill the previously declared structures as follows:
                // (1) untracked_data: Data of the files that have not yet been captured or saved.
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            }
        }

        std::cout << "old_data" << std::endl;
        for (auto data : old_data) {
            std::cout << "data.file -> " << data.file << std::endl;
            std::cout << "data.hash-> " << data.file_hash << std::endl;
        }
        std::cout << "*************" << std::endl;
        std::cout << "catched_not_modified" << std::endl;
        for (auto data : catched_not_modified) {
            std::cout << "data.file -> " << data << std::endl;
        }
        std::cout << "*************" << std::endl;
        std::cout << "catched_modified_data" << std::endl;
        for (auto data : catched_modified_data) {
            std::cout << "data.file -> " << data.file << std::endl;
            std::cout << "data.hash -> " << data.file_hash << std::endl;
        }
        std::cout << "*************" << std::endl;
        std::cout << "saved_modified_data" << std::endl;
        for (auto data : saved_modified_data) {
            std::cout << "data.file -> " << data.file << std::endl;
            std::cout << "data.hash -> " << data.file_hash << std::endl;
        }
        std::cout << "*************" << std::endl;
        std::cout << "untracked_data" << std::endl;
        for (auto data : untracked_data) {
            std::cout << "data.file -> " << data.file << std::endl;
            std::cout << "data.hash -> " << data.file_hash << std::endl;
        }
        std::cout << "*************" << std::endl;


        
        Builder builder;
        // We check the status of the containers. A container with data must always be processed.
        if (!old_data.empty()) {
            // We remove the versions stored in the container 'old_data' from the captured versions directory.
            // We remove the records from the captured versions database.
            builder.file_remover<vector<File>>(old_data, db_pos::version);
            builder.data_cleaner(base.db_catch_file);

            if (!catched_not_modified.empty()) { 
                // We insert the versions of the files whose most recent version is equal to the last version registered in the database of captured versions.
                builder.data_inserter<vector<string>>(catched_not_modified, base.db_catch_file);
            }
        }         
        /*if (!catched_not_modified.empty()) { 
            // We insert the versions of the files whose most recent version is equal to the last version registered in the database of captured versions.
            builder.data_inserter<vector<string>>(catched_not_modified, base.db_catch_file);
        }*/
        if (!catched_modified_data.empty()) {
            // We transport (copy and rename) the most recent versions of the files to the directory of captured versions.
            // We register the data of the versions in the database of captured versions.
            builder.file_transporter<vector<File>>(catched_modified_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(catched_modified_data, base.db_catch_file);
        }
        if (!saved_modified_data.empty()) { 
            // We transport (copy and rename) the most recent versions of the files to the directory of captured versions.
            // We register the data of the versions in the database of captured versions.
            builder.file_transporter<vector<File>>(saved_modified_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(saved_modified_data, base.db_catch_file);
        }
        if (!untracked_data.empty()) {
            // We transport (copy and rename) the most recent versions of the files to the directory of captured versions.
            // We register the data of the versions in the database of captured versions.
            builder.file_transporter<vector<File>>(untracked_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(untracked_data, base.db_catch_file);
        }
        
        printer.event_reporter(success_codes::version_catched);
    }
}

// Member function: drop_manager (). Invoked through the -drop command.
// According to the parameters sent, it must be determined which of the sub-functions will be executed.
// Remove single file version from standby phase: simple_drop_manager ().
// Remove all versions of all files in standby phase: multiple_drop_manager ().
void Manager::drop_manager() {
    if (arg_container[2] == process_all) {
        multiple_drop_manager();
    } else {
        simple_drop_manager();
    }
}

// Member function: simple_drop_manager ().
// Invoked through the -drop command and assigning as an additional parameter the file whose version will be removed.
// Ex: emi -drop relative_folder/file.txt
void Manager::simple_drop_manager() {
    Helper helper;
    Communicator printer;
    // We build the full path of the file whose version will be captured.
    string file = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // We validate the existence of the file.
    bool file_exists = helper.existence_checker<string>(file, status);
    if (file_exists) {
        File data;
        // We build the structure and fill it with the necessary information generated (based on the file) to capture the most recent version of the file.
        helper.data_organizer<File,string>(data, file, base.version_catch_path);
        // We look for the file that will be processed in the database of captured versions.
        // This is done in order to determine if a version of the file has already been captured previously.
        string catch_row = helper.row_extractor(data.file, base.db_catch_file);
        if (catch_row.empty()) {
            printer.warning_reporter(warning_codes::file_not_catched, drop_command);
        } else {
            Builder builder;
            // We extract all the records (rows) from the captured versions database excluding the record (row) that corresponds to the file we're working with.
            vector<string> protected_rows;
            helper.rows_extractor(protected_rows, base.db_catch_file, catch_row, action_mode::different_to_row);
            // We extract the record corresponding to the hash value of the version registered in the database of captured versions.
            // We compare the hash value of the version stored in the database and the hash value of the current file version.
            // We do this in order to determine if the file was modified after it was captured.
            string temporal_file_hash;
            helper.content_extractor<string,string>(temporal_file_hash, catch_row, db_pos::file_hash);
            bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
            if (is_same_hash) {
                // We extract the record corresponding to the full name of the version registered in the database of captured versions.
                string temporal_version;
                helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                // We remove the version found in the captured versions directory.
                // We remove the records from the captured versions database.
                // We insert the records previously extracted into the database of captured versions.
                builder.file_remover<string>(temporal_version);
                builder.data_cleaner(base.db_catch_file);
                builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);

                printer.event_reporter(success_codes::version_dropped);
            } else {
                // We request the authorization of the user to continue with the operations.
                printer.authorization_reporter(drop_command);
                string authorization;
                std::cin >> authorization;
                if (authorization == confirmed_auth) {
                    // We extract the record corresponding to the full name of the version registered in the database of captured versions.
                    string temporal_version;
                    helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                    // We remove the version found in the captured versions directory.
                    // We remove the records from the captured versions database.
                    // We insert the records previously extracted into the database of captured versions.
                    builder.file_remover<string>(temporal_version);
                    builder.data_cleaner(base.db_catch_file);
                    builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);

                    printer.event_reporter(success_codes::version_dropped);
                } else if (authorization == denied_auth) {
                    printer.event_reporter(notification_codes::cancelled_action, drop_command);
                } else {
                    printer.warning_reporter(warning_codes::unknown_authorization);
                }
            }
        }
    } else {
        printer.warning_reporter(warning_codes::file_not_found);
    }
}

// Member function: multiple_drop_manager ().
// Invoked through the -drop command and assigning the "all" subcommand as an additional parameter.
// Ex. emi -drop all
void Manager::multiple_drop_manager() {
    // We create the necessary containers to store the information of:
    // (1) untracked_files: Files that do not yet have a version captured by the -catch command.
    // (2) modified_files: Files that differ from their most recent captured or saved version.
    // (3) standby_files: Files that have a captured version and at the same time placed in the standby stage using the -catch command.
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> catched_files;
    Helper helper;
    Communicator printer;
    // We fill the container "untracked_files" only with the files that are not registered in the list of ignored files.
    // The hash value of the latest version of the file and the full path of the file will be saved.
    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // We validate if the database of captured versions is empty or has records.
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        Builder builder;	
        // We create the necessary containers to process the information:
        // (1) catched_modified: Files whose most recent version is different from the last captured version.
        // (2) catched_not_modified: Files whose most recent version is equal to their last captured version.
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        // We fill the containers of type "unordered_map" with the respective information.
        // At this point we only process the data from the captured versions database.
        // The database of saved versions will be analyzed later.
        helper.status_organizer(untracked_files, modified_files, catched_files, base.db_catch_file);
        // We fill the containers of type "vector" with the data processed and stored in modified_files and standby_files.
        helper.processed_files_organizer(catched_modified, catched_not_modified, modified_files, catched_files, base.db_catch_file);
        // We validate that there are files whose most recent versions are different from the last captured version.
        if (catched_modified.empty()) {
            vector<File> catched_not_modified_data;
            // We fill the previously declared structures as follows:
            // (1) catched_not_modified: Files whose most recent version is equal to their last captured version.
            // This data is extracted from the records of the captured version database (action_mode::built).
            helper.data_organizer<vector<File>,vector<string>>(catched_not_modified_data, catched_not_modified, base.version_catch_path, action_mode::built);
            // We check the status of the containers. A container with data must always be processed.
            if (!catched_not_modified_data.empty()) {
                // We remove the versions stored in the container 'catched_not_modified_data' from the captured versions directory.
                // We remove the records from the captured versions database.
                builder.file_remover<vector<File>>(catched_not_modified_data, db_pos::version);
                builder.data_cleaner(base.db_catch_file);
            }
            printer.event_reporter(success_codes::version_dropped);
        } else {
            // We request the authorization of the user to continue with the operations.
            printer.authorization_reporter(drop_command);
            string authorization;
            std::cin >> authorization;
            if (authorization == confirmed_auth) {
                vector<File> catched_modified_data;
                vector<File> catched_not_modified_data;
                // We fill the previously declared structures as follows:
                // (1) catched_modified_data: Data of the files whose most recent version is different from the last captured version.
                // This data is extracted from the records of the captured version database (action_mode::built).
                // (2) catched_not_modified_data: Data of the files whose most recent version is equal to their last captured version.
                // This data is extracted from the records of the captured version database (action_mode::built).
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_not_modified_data, catched_not_modified, base.version_catch_path, action_mode::built);
                // We check the status of the containers. A container with data must always be processed.
                if (!catched_modified_data.empty()) {
                    // We remove the versions stored in the container 'catched_modified_data' from the captured versions directory.
                    // We remove the records from the captured versions database.
                    builder.file_remover<vector<File>>(catched_modified_data, db_pos::version);
                    builder.data_cleaner(base.db_catch_file);
                }
                if (!catched_not_modified_data.empty()) {
                    // We remove the versions stored in the container 'catched_not_modified_data' from the captured versions directory.
                    // We remove the records from the captured versions database.
                    builder.file_remover<vector<File>>(catched_not_modified_data, db_pos::version);
                    builder.data_cleaner(base.db_catch_file);
                }
                printer.event_reporter(success_codes::version_dropped);
            } else if (authorization == denied_auth) {
                printer.event_reporter(notification_codes::cancelled_action, drop_command);
            } else {
                printer.warning_reporter(warning_codes::unknown_authorization);
            }
        }
    } else {
        printer.warning_reporter(warning_codes::no_files_to_process, drop_command);
    }
}

// Member function: snapshot_manager ().
// Invoked through the -snapshot command and assigning as an additional parameter a descriptive message of the saved version (s).
// Ex. emi -snapshot "This is a descriptive comment"
void Manager::snapshot_manager() {
    Communicator printer;
    Helper helper;
    // We validate if the database of captured versions is empty or has records.
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        // We extract the records corresponding to the full name of the versions registered in the database of captured versions.
        vector<string> version_names;
        helper.content_extractor<vector<string>,string>(version_names, base.db_catch_file, db_pos::version);
        // We verify that the paths of the captured versions are correct and the files exist.
        unordered_map<string,bool> status;
        bool versions_exist = helper.existence_checker<vector<string>>(version_names, status);
        if (versions_exist) {
            Builder builder(base);
            string timepoint;
            vector<string> catch_file_rows;
            // We extract all the records from the captured versions database.
            helper.rows_extractor(catch_file_rows, base.db_catch_file);
            // We capture the exact time point in which the process is running.
            // We generate a unique hash value using the previously generated time point.
            helper.timepoint_generator(timepoint);
            unsigned int timepoint_hash = helper.hash_generator(timepoint, action_mode::simple);
            // We transport a copy of the versions stored in the captured versions directory to a temporary sub-folder within the saved versions directory.
            builder.file_transporter<vector<string>>(version_names, base.version_main_path, version_temp);
            // We remove the versions stored in the container 'version_names' from the captured versions directory.
            builder.file_remover<vector<string>>(version_names);
            // We remove the records from the captured versions database.
            builder.data_cleaner(base.db_catch_file);
            // Rename the temporary sub-folder created within the saved file versions directory.
            // The new directory name will be the previously created hash value.
            builder.file_renamer(std::to_string(timepoint_hash), base.version_main_path, version_temp);
            // We save the records extracted from the database of captured versions in the database of saved versions.
            // Additionally, the pending values necessary to complete the structure are registered.
            // These additional values are: identifier hash value, execution time, and comment.
            builder.data_saver(catch_file_rows, base.db_main_file, timepoint, std::to_string(timepoint_hash), arg_container[2]);
            printer.event_reporter(success_codes::version_saved);
        } else {
            printer.error_reporter(error_codes::inconsistency_detected, snapshot_command);
        }
    } else {
        printer.warning_reporter(warning_codes::no_files_to_process, snapshot_command);
    }
}

// Member function: look_manager ().
// Invoked through the -look command.
// Ex. emi -look 
void Manager::look_manager() {
    // We create the necessary containers to store the information of:
    // (1) untracked_files: Files that do not yet have a version captured by the -catch command.
    // (2) modified_files: Files that differ from their most recent captured or saved version.
    // (3) standby_files: Files that have a captured version and at the same time placed in the standby stage using the -catch command.
    // (4) saved_files: Files that have a version saved using the -snapshot command.
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;
    // We fill the container "untracked_files" only with the files that are not registered in the list of ignored files.
    // The hash value of the latest version of the file and the full path of the file will be saved.
    vector<string> ignored_files_or_folders;
    Helper helper;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // We validate that there are available files (that is, files that have not been ignored, captured or saved before).
    Communicator printer;
    if (untracked_files.empty()) {
        printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
    } else {
        // We validate if the database of captured versions is empty or has records.
        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            // We fill the containers of type "unordered_map" with the respective information.
            // At this point we only process the data from the captured versions database.
            // The database of saved versions will be analyzed later.
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            // We validate if the database of saved versions is empty or has records.
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // We fill the containers of type "unordered_map" with the respective information.
                // At this point we only process the data from the saved versions database.
                // The database of captured versions was previously analyzed so this activity completes the filling of the containers.
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            }
        } else {
            // We validate if the database of saved versions is empty or has records.
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // We fill the containers of type "unordered_map" with the respective information.
                // At this point we only process the data from the saved versions database.
                // The database of captured versions was not analyzed because it is empty.
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            }
        }
    }
}

// Member function: log_manager ().
// Invoked through the -log command.
// Ex. emi -log 
void Manager::log_manager() {
    Log log;
    // We create the necessary containers to store the information of:
    // (1) log_info: Structure that contains the data generated when applying the -snapshot command. 
    // This data is: Snapshot code (hash value), snapshot date and comment.
    // (2) saved_files: Files whose versions have been saved. Each file is associated with the unique hash value generated when the -snapshot command was applied.
    vector<Log> log_info;
    unordered_multimap<string,string> saved_files;

    Helper helper;
    Communicator printer;
    // We validate if the database of saved versions is empty or has records.
    bool main_has_data = helper.content_checker(base.db_main_file);
    if (main_has_data) {
        // We extract all the records from the saved versions database.
        vector<string> main_file_rows;
        helper.rows_extractor(main_file_rows, base.db_main_file);
        // We fill the containers based on the records extracted from the database of saved versions.
        helper.log_organizer(log, log_info, saved_files, main_file_rows);
        // We send the containers with the necessary information to the function that will print the results.
        printer.log_reporter(log_info, saved_files, current_path);
    } else {
        // We send the containers with the necessary information to the function that will print the results.
        // In this case the containers will be empty so the user will be informed that there are no records.
        printer.log_reporter(log_info, saved_files, current_path);
    }
}

// Member function: ignore_manager ().
// Invoked through the -ignore command and assigning the file to be ignored as an additional parameter.
// Ex: emi -ignore relative_folder/file.txt
void Manager::ignore_manager() {
    Communicator printer;
    Helper helper;
    // We build the full path of the file whose version will be captured.
    string file_or_folder = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // We validate the existence of the file.
    bool file_exists = helper.existence_checker<string>(file_or_folder, status);
    if (file_exists) {
        // We look for the file that will be processed in the database of captured versions and in the database of saved versions.
        // This is done in order to determine if a version of the file has already been captured or saved previously.
        string catch_row = helper.row_extractor(file_or_folder, base.db_catch_file);
        string main_row = helper.row_extractor(file_or_folder, base.db_main_file);
        if (catch_row.empty() && main_row.empty()) {
            // We validate that the file is not registered in the list of ignored files.
            bool file_or_folder_is_ignored = helper.ignored_file_checker(file_or_folder, base.config_ignore_file);
            if (file_or_folder_is_ignored) {
                printer.warning_reporter(warning_codes::file_already_ignored, ignore_command);
            } else {
                Builder builder;
                // We insert the full path of the file in the ignore file.
                builder.data_inserter<string>(file_or_folder, base.config_ignore_file);
                printer.event_reporter(success_codes::file_ignored);
            }        
        } else {
            printer.warning_reporter(warning_codes::file_in_use, ignore_command);        
        }
    } else {
        printer.warning_reporter(warning_codes::file_not_found);
    }
}

// Member function: get_manager ().
// Invoked through the -get command and assigning as an additional parameter the snapshot code related to the versions to be restored.
// Ex: emi -get 123456789
void Manager::get_manager() {
    Communicator printer;
    Helper helper;

    string snapshot_code = arg_container[2];
    // We build the full path of the file whose version will be captured.
    string target_directory = helper.location_generator(arg_container[2], current_path);
    vector<string> main_file_rows;
    // We extract the records from the saved versions database whose value of the snapshot code is equal to the code entered by the user.
    helper.rows_extractor(main_file_rows, base.db_main_file, snapshot_code, action_mode::similar_to_item, db_pos::snap_hash);
    if (main_file_rows.empty()) {
        printer.warning_reporter(warning_codes::snapcode_not_found);
    } else {
        Builder builder;
        vector<string> main_version_names;
        // We extract the names of the versions of the group of records filtered previously.
        helper.content_extractor<vector<string>,vector<string>>(main_version_names, main_file_rows, db_pos::snap_version);
        // We request the authorization of the user to continue with the operations.
        printer.authorization_reporter(get_command);
        string authorization;
        std::cin >> authorization;
        // User authorized to keep current files and bring saved versions to temporary directory.
        if (authorization == keep_auth) {
            // We create the directory that will contain the saved versions.
            builder.directory_builder<string>(target_directory);
            // We transport a copy of the versions to the directory created previously.
            builder.file_transporter<vector<string>>(main_version_names, target_directory);
            printer.event_reporter(success_codes::version_restored);
        // The user authorized to replace the current files with the saved versions.
        } else if (authorization == replace_auth) {
            // We extract the paths of the saved versions that we bring back.
            vector<string> path_names;
            helper.content_extractor<vector<string>,vector<string>>(path_names, main_file_rows, db_pos::path_name);
            // We extract the file names of the saved versions that we bring back.
            vector<string> file_names;
            helper.content_extractor<vector<string>,vector<string>>(file_names, main_file_rows, db_pos::file);
            // We remove duplicate paths temporarily.
            helper.duplicate_organizer(path_names);
            // We verify the existence of the paths and files that will be brought back.
            unordered_map<string,bool> directories_and_status;
            helper.existence_checker<vector<string>>(path_names, directories_and_status);
            unordered_map<string,bool> files_and_status;
            helper.existence_checker<vector<string>>(file_names, files_and_status);
            // We remove the current files to make it possible for the saved versions to be restored without errors.
            builder.file_remover<unordered_map<string,bool>>(files_and_status);
            // We create the necessary directories to place the saved versions that will be restored.
            builder.directory_builder<unordered_map<string,bool>>(directories_and_status);
            // We restore the saved versions to their corresponding locations.
            builder.special_transporter(main_version_names, file_names);
            printer.event_reporter(success_codes::version_restored);
        } else if (authorization == denied_auth) {
            printer.event_reporter(notification_codes::cancelled_action, get_command);
        } else {
            printer.warning_reporter(warning_codes::unknown_authorization);
        }
    }
}

// Member function: restart_manager ().
// Invoked through the -restart command.
// Ex. emi -restart 
void Manager::restart_manager() {
    Communicator printer;
    printer.authorization_reporter(restart_command);
    // We request the authorization of the user to continue with the operations.
    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder(base);
        // We remove the emi repository including all its internal files (action_mode::recursive)
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        // We build the emi repository with its basic configuration.
        builder.repository_builder(current_path);
        printer.event_reporter(success_codes::emi_repository_restarted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, restart_command);
    } else {
        printer.warning_reporter(warning_codes::unknown_authorization);
    }
}

// Member function: bye_manager ().
// Invoked through the -bye command.
// Ex. emi -bye 
void Manager::bye_manager() {
    Communicator printer;
    // We request the authorization of the user to continue with the operations.
    printer.authorization_reporter(bye_command);
    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder;
        // We remove the emi repository including all its internal files (action_mode::recursive)
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        printer.event_reporter(success_codes::emi_repository_deleted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, bye_command);
    } else {
        printer.warning_reporter(warning_codes::unknown_authorization);
    }
}

Manager::~Manager() {}
