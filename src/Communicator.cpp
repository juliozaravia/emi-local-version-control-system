#include <iostream>
#include <string>

#include "../include/Communicator.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_multimap;

Communicator::Communicator() {}

void Communicator::event_reporter(int com_identifier, const std::string& command, const char* error_description) {
    if (com_identifier == success_codes::emi_repository_created) {
        cout << "[Success Code: SC" << success_codes::emi_repository_created << "] The emi repository has been created successfully." << endl;
        cout << "Tip: Use the -look command to view files without tracking." << endl;
    } else if (com_identifier == success_codes::version_catched) {
        cout << "[Success Code: SC" << success_codes::version_catched << "] The latest version(s) of the file(s) has been successfully put on standby stage." << endl;
        cout << "Tip: Use -snapshot to save all standby versions. (Usage info: Use --help)" << endl;
    } else if (com_identifier == success_codes::version_saved) {
        cout << "[Success Code: SC" << success_codes::version_saved << "] The latest version of the files found in the standby stage have been successfully saved." << endl;
        cout << "Tip: Use -log to see all saved versions. (Usage info: Use --help)" << endl;
    } else if (com_identifier == success_codes::file_ignored) {
        cout << "[Success Code: SC" << success_codes::file_ignored << "] The file / directory has been successfully registered in the ignore list." << endl;
        // como se ven los archivos ignorados.
        // como se ven los archivos ignorados.
    } else if (com_identifier == success_codes::emi_repository_restarted) {
        cout << "[Success Code: SC" << success_codes::emi_repository_restarted << "] The emi repository has been successfully restarted." << endl;
    } else if (com_identifier == success_codes::emi_repository_deleted) {
        cout << "[Success Code: SC" << success_codes::emi_repository_deleted << "] The emi repository has been successfully deleted." << endl;
    } else if (com_identifier == success_codes::version_dropped) {
        cout << "[Success Code: SC" << success_codes::version_dropped << "] The file has been successfully dropped from the standby stage." << endl;
    } else if (com_identifier == warning_codes::emi_repository_exists) {
        cout << "[Warning Code: WC" << warning_codes::emi_repository_exists << "] The emi repository already exists." << endl;
        cout << "Tip: Use the -look command to view files without tracking." << endl;
    } else if (com_identifier == warning_codes::parent_emi_repository_exists) {
        cout << "[Warning Code: WC" << warning_codes::parent_emi_repository_exists << "] The emi repository already exists in a parent directory." << endl;
        cout << "To use the emi commands you must be located in the root directory where the emi repository was created." << endl;
    } else if (com_identifier == warning_codes::file_not_open) {
        cout << "An error occurred while applying the " << command << " command." << endl;
        if (command == catch_command) {
            cout << "Check the existence of the file(s) or that the read / write permissions are enabled." << endl;
        } else if (command == snapshot_command) {
            cout << "Some base files could not be used due to a read / write problem." << endl;
        }
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: (" << command << ") EC" << warning_codes::file_not_open << "]" << endl;
        cout << error_description << endl;
    } else if (com_identifier == warning_codes::unknown_command) {
        cout << "[Warning Code: WC" << warning_codes::unknown_command << "] The command entered doesn't exist, is misspelled or is not being used correctly." << endl;
        cout << "Use --help, to get the authorized commands and learn how to use them correctly." << endl;
    } else if (com_identifier == warning_codes::identical_version_in_standby) {
        cout << "[Warning Code: WC" << warning_codes::identical_version_in_standby << "] An identical version of this file already exists in the standby stage." << endl;
        cout << "Tip: Use -snapshot to save all standby versions. (Usage info: Use --help)" << endl;
    } else if (com_identifier == warning_codes::identical_version_saved) {
        cout << "[Warning Code: WC" << warning_codes::identical_version_saved << "] An identical version of this file has already been saved." << endl;
        cout << "Tip: Use -log to get a list of the currently saved files. (Usage info: Use --help)" << endl;
    } else if (com_identifier == warning_codes::emi_repository_not_exists) {
        cout << "[Warning Code: WC" << warning_codes::emi_repository_not_exists << "] The emi repository has not yet been created. :(" << endl;
        cout << "To use the emi commands you must create an emi repository before." << endl;
        cout << "Tip: Use -start command to create an emi repository. (Usage info: Use --help)" << endl;
    } else if (com_identifier == warning_codes::wrong_amount_of_commands) {
        cout << "[Warning Code: WC" << warning_codes::wrong_amount_of_commands << "] The number of commands entered is incorrect." << endl;
        cout << "Use --help, to get the authorized commands and how to use them correctly." << endl;
    } else if (com_identifier == warning_codes::no_files_to_save) {
        cout << "[Warning Code: WC" << warning_codes::no_files_to_save << "] No files were found in the standby stage." << endl;
        cout << "Tip: Use -snapshot after you have put files in the standby stage using -catch. (Usage info: Use --help)" << endl;
    } else if (com_identifier == warning_codes::file_not_found) {
        cout << "[Warning Code: WC" << warning_codes::file_not_found << "] The file / directory entered doesn't exist, is misspelled or is not a relative path.";
    } else if (com_identifier == warning_codes::file_already_ignored) {
        cout << "[Warning Code: WC" << warning_codes::file_already_ignored << "] The file / directory entered has previously been registered in the ignore list." << endl;
        if (command == catch_command) {
            cout << "Tip: To use -catch the target file must not be registered in the ignore list. (Usage info: Use --help)" << endl;
        }
    } else if (com_identifier == warning_codes::unknown_authorization) {
        cout << "[Warning Code: WC" << warning_codes::unknown_authorization << "] The command entered is not correct or is misspelled." << endl;
        cout << "Tip: Write the command exactly as requested. Respect upper and lower case." << endl;
    } else if (com_identifier == warning_codes::file_not_catched) {
        cout << "[Warning Code: WC" << warning_codes::file_not_catched << "] The file entered  has not been found in the standby stage." << endl;
        cout << "Tip: To use " << command << " the target file must be in standby stage. (Usage info: Use --help)" << endl;
    } else if (com_identifier == warning_codes::file_in_use) {
        cout << "[Warning Code: WC" << warning_codes::file_in_use << "] The entered file has a version previously saved or located in the standby stage." << endl;
        cout << "Tip: To use " << command << " on the target file it must not have previously been affected by " << catch_command  << " or " << snapshot_command << ". (Usage info: Use --help)" << endl;
    } else if (com_identifier == error_codes::emi_directories_not_created) {
        cout << "An error occurred while applying the -start command." << endl;
        cout << "Some base configuration folders could not be created." << endl;
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: EC" << error_codes::emi_directories_not_created << "]" << endl;
        cout << error_description << endl;
    } else if (com_identifier == error_codes::emi_files_not_created) {
        cout << "An error occurred while applying the -start command." << endl;
        cout << "Some base configuration files could not be created." << endl;
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: EC" << error_codes::emi_files_not_created << "]" << endl;
        cout << error_description << endl;
    } else if (com_identifier == error_codes::emi_unknown_error) {
        cout << "An error occurred while applying the " << command << " command." << endl;
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: (" << command << ") EC" << error_codes::emi_unknown_error << "]" << endl;
        cout << error_description << endl;
    } else if (com_identifier == error_codes::unsuccessful_file_manipulation) {
        cout << "An error occurred while applying the " << command << " command." << endl;
        cout << "The file manipulation process did not complete successfully." << endl;
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: (" << command << ") EC" << error_codes::unsuccessful_file_manipulation << "]" << endl;
        cout << error_description << endl;
    } else if (com_identifier == error_codes::inconsistency_detected) {
        cout << "An error occurred while applying the " << command << " command." << endl;
        cout << "The file manipulation process did not complete successfully." << endl;
        cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
        cout << "************* Copy and send the following information *************" << endl;
        cout << "[Error Code: (" << command << ") EC" << error_codes::inconsistency_detected << "]" << endl;
    } else if (com_identifier == notification_codes::cancelled_action) {
        cout << "[Notification Code: NC" << notification_codes::cancelled_action << "] The action requested by " << command << " has been canceled." << endl;
    } else if (com_identifier == notification_codes::no_files_found) {
        cout << "[Notification Code: NC" << notification_codes::no_files_found << "] No files are available to apply the " << command << " command." << endl;
    }
}

void Communicator::command_reporter() {
    cout << "-start\t\t: Create an empty emi repository." << endl;
    cout << "\t\tExample: emi -start" << endl;
    cout << endl;
    cout << "-look\t\t: List of all files grouped as tracked and untracked." << endl;
    cout << "\t\tExample: emi -look" << endl;
    cout << endl;
    cout << "-catch\t\t: Allows you to record the changes (new versions) made in a file." << endl;
    cout << "\t\tExample (file in internal path): emi -catch my_sub_path\\my_file.file_format \"Comment describing the new version\"" << endl;
    cout << "\t\tExample (file in base path): emi -catch my_file.file_format \"Comment describing the new version\"" << endl;
    cout << endl;
    cout << "--help\t\t: List of all the commands and the way to use them correctly." << endl;
    cout << "--version\t: Current version of emi software." << endl;
}

void Communicator::version_reporter() {
    cout << "EMI Control Version System - Version 1.0.0" << endl;
    cout << "Copyright (C) 2020 - Julio Zaravia" << endl;
    cout << "This is free software. There is NO warranty; not even for" << endl;
    cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << endl;
}

void Communicator::status_reporter(const unordered_map<string,string>& untracked_files,
                                   const unordered_map<string,string>& modified_files,
                                   const unordered_map<string,string>& standby_files) {
    cout << "------------------------" << endl;
    cout << "Standby files | Total: " << standby_files.size() << endl;
    cout << "------------------------" << endl;

    if (standby_files.empty()) {
        cout << "There are no files on standby stage." << endl;
    } else {
        for (auto item : standby_files) {
            cout << item.first << " - " << item.second << endl;
        }
    }

    cout << endl;

    cout << "-------------------------" << endl;
    cout << "Modified files | Total: " << modified_files.size() << endl;
    cout << "-------------------------" << endl;

    if (modified_files.empty()) {
        cout << "There are no modified files." << endl;
    } else {
        for (auto item : modified_files) {
            cout << item.first << " - " << item.second << endl;
        }
    }

    cout << endl;

    cout << "--------------------------" << endl;
    cout << "Untracked files | Total: " << untracked_files.size() << endl;
    cout << "--------------------------" << endl;

    if (untracked_files.empty()) {
        cout << "There are no untracked files." << endl;
    } else {
        for (auto item : untracked_files) {
            cout << item.first << " - " << item.second << endl;
        }
    }
}

void Communicator::log_reporter(const vector<Log>& log_info, const unordered_multimap<string,string>& saved_files) {
    if (log_info.empty()) {
        cout << "There are no saved versions." << endl;
        cout << "Tip: Use -snapshot to save the versions in the standby stage. (Usage info: Use --help)" << endl;
    } else {
        cout << "--------------------------" << endl;
        cout << "Snapshots made | Total: " << log_info.size() << endl;
        cout << "--------------------------" << endl;
        cout << endl;
        unsigned int temp_counter = 0;
        for (auto log_item : log_info) {
            cout << "Snapshot code: " << log_item.snapshot_code << endl;
            cout << "Date: " << log_item.snapshot_date << endl;
            cout << "Comment: " << log_item.snapshot_comment << endl;
            cout << "Saved versions:" << endl;
            for (auto file : saved_files) {
                if (log_item.snapshot_code == file.first) {
                    cout << "> " << file.second << endl;
                }
            }

            temp_counter++;
            if (temp_counter != log_info.size()) {
                cout << endl;
                cout << "..............................." << endl;
                cout << endl;
            }
        }
    }
}

void Communicator::authorization_reporter(const string& command) {
    string action;
    string first_comment;
    string second_comment;
    if (command == restart_command) {
        action = "restart the emi repository";
        first_comment = "All saved versions will be deleted.";
        second_comment = "The repository will return to its initial state.";
    } else if (command == bye_command) {
        action = "delete the emi repository";
        first_comment = "All saved versions will be deleted.";
        second_comment = "This action can not be undone.";
    } else if (command == drop_command) {
        action = "remove this file from the standby stage";
        first_comment = "The file in the standby stage is different from its original version.";
        second_comment = "This action can not be undone";
    }
    cout << "Do you want to " << action << "?" << endl;
    cout << first_comment << endl;
    cout << second_comment << endl;
    cout << "Type " << confirmed_auth << " to authorize or " << denied_auth << " to cancel:" << endl;
}

Communicator::~Communicator() {}

