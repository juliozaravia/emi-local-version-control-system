/*
 * Project: Emi Local Version Control System 
 * File: Communicator Class - Implementation file 
 * Description: It allows us to print success, alert and error messages on the screen.
 * @author
 * Julio Zaravia <hey@juliozaravia.com>
 */

#include <iostream>
#include <iomanip>
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

// Description: It allows us to print notifications or success messages associated with any requested operation on the screen.
void Communicator::event_reporter(int com_identifier, const std::string& command) {
    if (com_identifier == success_codes::emi_repository_created) {
        cout << "[Success Code: SC" << success_codes::emi_repository_created << "] The emi repository has been created successfully." << endl;
        cout << "Tip: Use the -look command to view the untracked files. (Usage info: Use --help)" << endl;
    } else if (com_identifier == success_codes::version_catched) {
        cout << "[Success Code: SC" << success_codes::version_catched << "] The latest version(s) of the file(s) has(have) been successfully put on standby stage." << endl;
        cout << "Tip: Use -snapshot to save all standby versions. (Usage info: Use --help)" << endl;
    } else if (com_identifier == success_codes::version_saved) {
        cout << "[Success Code: SC" << success_codes::version_saved << "] The latest version(s) of the file(s) captured in the standby stage have been successfully saved." << endl;
        cout << "Tip: Use -log to see all saved versions. (Usage info: Use --help)" << endl;
    } else if (com_identifier == success_codes::file_ignored) {
        cout << "[Success Code: SC" << success_codes::file_ignored << "] The file / directory has been successfully registered in the ignore list." << endl;
    } else if (com_identifier == success_codes::emi_repository_restarted) {
        cout << "[Success Code: SC" << success_codes::emi_repository_restarted << "] The emi repository has been successfully restarted." << endl;
    } else if (com_identifier == success_codes::emi_repository_deleted) {
        cout << "[Success Code: SC" << success_codes::emi_repository_deleted << "] The emi repository has been successfully deleted." << endl;
    } else if (com_identifier == success_codes::version_dropped) {
        cout << "[Success Code: SC" << success_codes::version_dropped << "] The file(s) has(have) been successfully dropped from the standby stage." << endl;
    } else if (com_identifier == success_codes::version_restored) {
        cout << "[Success Code: SC" << success_codes::version_restored << "] The file(s) has(have) been successfully restored." << endl;
    } else if (com_identifier == notification_codes::cancelled_action) {
        cout << "[Notification Code: NC" << notification_codes::cancelled_action << "] The action requested by " << command << " has been canceled." << endl;
    } else if (com_identifier == notification_codes::no_files_found) {
        cout << "[Notification Code: NC" << notification_codes::no_files_found << "] No files are available to apply the " << command << " command." << endl;
    }
}

// Description: It allows us to print on the screen the alert messages associated with any requested operation.
void Communicator::warning_reporter(int warning_identifier, const std::string& command) {
    if (warning_identifier == warning_codes::emi_repository_exists) {
        cout << "[Warning Code: WC" << warning_codes::emi_repository_exists << "] The emi repository already exists." << endl;
    } else if (warning_identifier == warning_codes::parent_emi_repository_exists) {
        cout << "[Warning Code: WC" << warning_codes::parent_emi_repository_exists << "] The emi repository already exists in a parent directory." << endl;
        cout << "To use the emi commands you must be located in the root directory where the emi repository was created." << endl;
    } else if (warning_identifier == warning_codes::unknown_command) {
        cout << "[Warning Code: WC" << warning_codes::unknown_command << "] The command entered doesn't exist, is misspelled or is not being used correctly." << endl;
    } else if (warning_identifier == warning_codes::identical_version_in_standby) {
        cout << "[Warning Code: WC" << warning_codes::identical_version_in_standby << "] An identical version of this file already exists in the standby stage." << endl;
        cout << "Use -snapshot to save all captured versions in the standby stage." << endl;
    } else if (warning_identifier == warning_codes::identical_version_saved) {
        cout << "[Warning Code: WC" << warning_codes::identical_version_saved << "] An identical version of this file has already been saved." << endl;
        cout << "Tip: Use -log to get a list of the currently saved files." << endl;
    } else if (warning_identifier == warning_codes::emi_repository_not_exists) {
        cout << "[Warning Code: WC" << warning_codes::emi_repository_not_exists << "] The emi repository has not yet been created." << endl;
        cout << "To use the emi commands you must create an emi repository before." << endl;
        cout << "Use -start to create an emi repository." << endl;
    } else if (warning_identifier == warning_codes::wrong_amount_of_commands) {
        cout << "[Warning Code: WC" << warning_codes::wrong_amount_of_commands << "] The number of commands / parameters entered is incorrect." << endl;
    } else if (warning_identifier == warning_codes::no_files_to_process) {
        cout << "[Warning Code: WC" << warning_codes::no_files_to_process << "] No captured versions were found in the standby stage." << endl;
        cout << "To use " << command << " you must first capture some versions using -catch." << endl;
    } else if (warning_identifier == warning_codes::file_not_found) {
        cout << "[Warning Code: WC" << warning_codes::file_not_found << "] The file / directory entered doesn't exist, is misspelled or is not a relative path." << endl;
    } else if (warning_identifier == warning_codes::file_already_ignored) {
        cout << "[Warning Code: WC" << warning_codes::file_already_ignored << "] The entered file / directory is registered in the list of ignored files." << endl;
        if (command == catch_command) { cout << "To use " << command << " the target file must not be registered in the ignore list." << endl; }
    } else if (warning_identifier == warning_codes::unknown_authorization) {
        cout << "[Warning Code: WC" << warning_codes::unknown_authorization << "] The command entered is not correct or is misspelled." << endl;
        cout << "Write the command exactly as requested. Respect upper and lower case." << endl;
    } else if (warning_identifier == warning_codes::file_not_catched) {
        cout << "[Warning Code: WC" << warning_codes::file_not_catched << "] The file entered  has not been found in the standby stage." << endl;
        cout << "To use " << command << " the target file must be in standby stage." << endl;
    } else if (warning_identifier == warning_codes::file_in_use) {
        cout << "[Warning Code: WC" << warning_codes::file_in_use << "] The entered file has a version previously captured via " << catch_command << " or saved via " << snapshot_command << endl;
        cout << "To use " << command << ", the target file must not have a previously captured or saved version." << endl;
    } else if (warning_identifier == warning_codes::snapcode_not_found) {
        cout << "[Warning Code: WC" << warning_codes::snapcode_not_found<< "] The code entered does not refer to any version registered in the saved files database." << endl;
        cout << "Use " << log_command << " to make sure that the snapshot code you entered exists and is correctly written." << endl;
    } 
    cout << "Tip: Use --help, to get the authorized commands and how to use them correctly." << endl;
}

// Description: It allows us to print on the screen the error messages associated with any requested operation.
void Communicator::error_reporter(int error_identifier, const std::string& command, const char* error_description) {
    cout << "An error occurred while applying the " << command << " command." << endl;
    cout << "The reasons for this unexpected error can be:" << endl;

    if (error_identifier == error_codes::unable_to_manipulate_files_or_directories) {
        cout << "- Some base configuration directories could not be created or removed." << endl;
        cout << "- Some base configuration files could not be created or removed." << endl;
        cout << "- Some file manipulation activities, like copy or rename files among others, were not completed successfully." << endl;
    } else if (error_identifier == error_codes::unable_to_open_files) {
        cout << "- The file entered does not have the read / write permissions correctly enabled." << endl;
        cout << "- If the process does not require entering a file, it is possible that some base file does not have read / write permissions correctly enabled." << endl;
    } else if (error_identifier == error_codes::inconsistency_detected) {
        cout << "The file manipulation process did not complete successfully." << endl;  
    } else if (error_identifier == error_codes::emi_unknown_error) {
        cout << "An error occurred while applying the " << command << " command." << endl;
    } 
    // Unlike the previous two methods, this method reports the specific error caught.
    cout << "Try again. If the error persists write to support@juliozaravia.com." << endl;
    cout << "************* Copy and send the following information *************" << endl;
    cout << "[Error Code: (" << command << ") EC" << error_identifier << "]" << endl;
    cout << error_description << endl;
}

// Description: It allows us to print on the screen the commands necessary for the proper use of the emi repository.
void Communicator::command_reporter() {
    const int first_column_width = 15;
    const int second_column_width = 40;
    const std::string separator = "********************";
    cout << "### Command: " << help_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to view a list of all allowed commands and their application.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi --help";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- This command can be executed without the need to create an emi repository." << endl;
    cout << endl;
    cout << "### Command: " << version_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to view the version and other additional details of the Emi project.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi --version";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- This command can be executed without the need to create an emi repository." << endl;
    cout << endl;
    cout << "### Command: " << start_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allow us to create a new clean emi repository.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -start";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- The repository is created in the current path under the name of emi_base." << endl;
    cout << "\t- The emi_base folder should not be deleted manually." << endl;
    cout << endl;
    cout << "### Command: " << look_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It shows us a list of files grouped according to their status.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -look";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- Saved versions are excluded from this list, they can be viewed through -log." << endl;
    cout << endl;
    cout << "### Command: " << catch_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It captures the latest version of a file and puts it in the standby stage.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "To capture a single file: the relative file path. To capture all available files: the 'all' subcommand.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -catch some_folder/file_to_capture or emi -catch all";
    cout << endl;
    cout << endl;
    cout << "### Command: " << drop_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to release a previously captured version from the standby stage.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "To release a single file: the relative file path. To release all captured files: the 'all' subcommand.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -drop some_folder/file_to_capture or emi -drop all";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- Only the versions of files captured by -catch that are in the standby stage can be released." << endl;
    cout << "\t- The file version cannot be released if the file has already been saved by applying -snapshot." << endl;
    cout << endl;
    cout << "### Command: " << ignore_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to register a file or directory in the ignore list. An ignored file or directory cannot be used by emi.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "The relative path of the file or directory to ignore.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -ignore some_folder/some_sub_folder/file_to_ignore";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- Files captured in the standby stage cannot be registered in the ignore list." << endl;
    cout << endl;
    cout << "### Command: " << snapshot_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to save all the captured versions in the standby stage.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "A descriptive comment of the versions that will be saved.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -snapshot \"This is a descriptive comment\"";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- Adding a comment as a parameter is required." << endl;
    cout << "\t- The comment must be enclosed in quotation marks to be valid." << endl;
    cout << "\t- The number of versions that will be saved when applying this command is equal to the number of captured versions." << endl;
    cout << endl;
    cout << "### Command: " << log_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It shows us a list of the saved versions grouping them by each application of -snapshot.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -log";
    cout << endl;
    cout << endl;
    cout << "### Command: " << get_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to restore all the saved versions that are related to each other by a unique code (snapshot code).";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "Unique code that was generated by -snapshot when it was applied.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -get 20665431001218";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- You can choose whether or not the saved versions replace the current versions when restored." << endl;
    cout << "\t- If the current version of a file is replaced by a saved version, the current version cannot be recovered." << endl;
    cout << endl;
    cout << "### Command: " << restart_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "It allows us to restart the emi repository and return all the configurations to their initial state.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -restart";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- Using this command irreversibly removes all versions and temporary files saved in the emi repository." << endl;
    cout << "\t- The use of this command irreversibly modifies all the settings made in the emi repository and returns them to their initial values." << endl;
    cout << "\t- User confirmation is required to apply this command." << endl;
    cout << endl;
    cout << endl;
    cout << "### Command: " << bye_command << endl;
    cout << separator << endl;
    cout << std::left << std::setw(first_column_width) << "# Description: ";
    cout << std::left << std::setw(second_column_width) << "iIt allows us to delete the emi repository completely.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# Parameters: ";
    cout << std::left << std::setw(second_column_width) << "It does not require parameters.";
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "# How to use: ";
    cout << std::left << std::setw(second_column_width) << "emi -bye";
    cout << endl;
    cout << "# Considerations: " << endl;
    cout << "\t- User confirmation is required to apply this command." << endl;
}

// Description: It allows us to print on the screen the version and additional informative data of the emi application.
void Communicator::version_reporter() {
    const int first_column_width = 11;
    const int second_column_width = 30;
    cout << "Emi Local Version Control System - Version 1.0" << endl;
    cout << "Copyright (C) 2020 - Julio Zaravia" << endl;
    cout << "**************************************************" << endl;
    cout << std::left << std::setw(first_column_width) << "LinkedIn:";
    cout << std::left << std::setw(second_column_width) << "www.linkedin.com/in/julio-zaravia"; 
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "GitHub:";
    cout << std::left << std::setw(second_column_width) << "www.github.com/juliozaravia"; 
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "Blog:";
    cout << std::left << std::setw(second_column_width) << "www.juliozaravia.com"; 
    cout << endl;
    cout << std::left << std::setw(first_column_width) << "E-mail:";
    cout << std::left << std::setw(second_column_width) << "hey@juliozaravia.com"; 
    cout << endl;
    cout << "**************************************************" << endl;
    cout << "This is free software made for learning purposes." << endl;
    cout << "Unfortunately there is no guarantee of anything :/" << endl;
    cout << "But feel free to modify and improve it." << endl;
    cout << "**************************************************" << endl;
    cout << "Made with love... very very very late at night." << endl;
    cout << "- From Puuu to Chiii." << endl;
}

// Description: It allows us to print the files available for processing on the screen, grouping them according to their status.
void Communicator::status_reporter(const unordered_map<string,string>& untracked_files,
        const unordered_map<string,string>& modified_files,
        const unordered_map<string,string>& standby_files,
        const string& current_path) {
    const int hash_width = 13;
    const int file_width = 30;
    
    cout << "------------------------" << endl;
    cout << "Standby files | Total: " << standby_files.size() << endl;
    cout << "------------------------" << endl;

    if (standby_files.empty()) {
        cout << "There are no files on standby stage." << endl;
    } else {
        for (auto item : standby_files) {
            cout << std::left << std::setw(hash_width) << item.first;
            cout << std::left << std::setw(file_width) << item.second.substr((current_path.size() + 1), item.second.size());
            cout << endl;
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
            cout << std::left << std::setw(hash_width) << item.first;
            cout << std::left << std::setw(file_width) << item.second.substr((current_path.size() + 1), item.second.size());
            cout << endl;
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
            cout << std::left << std::setw(hash_width) << item.first;
            cout << std::left << std::setw(file_width) << item.second.substr((current_path.size() + 1), item.second.size());
            cout << endl;
        }
    }
}

// Description: It allows us to print on the screen all the blocks of saved files, grouping them by their corresponding snapshot code.
void Communicator::log_reporter(const vector<Log>& log_info, const unordered_multimap<string,string>& saved_files, const string& current_path) {
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
                    cout << "> " << file.second.substr((current_path.size() + 1), file.second.size()) << endl;
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

// Description: It allows us to print on the screen an authorization request to carry out a specific operation.
void Communicator::authorization_reporter(const string& command) {
    vector<string> message;
    vector<string> options;

    if (command == restart_command) {
        message.push_back("Do you want to restart the emi repository?");
        message.push_back("All saved versions will be deleted.");
        message.push_back("The repository will return to its initial state.");

        options.push_back(confirmed_auth + " to autorize");
        options.push_back(" or " + denied_auth + " to cancel:");
    } else if (command == bye_command) {
        message.push_back("Do you want to delete the emi repository?");
        message.push_back("All saved versions will be deleted.");
        message.push_back("This action can not be undone.");

        options.push_back(confirmed_auth + " to autorize");
        options.push_back(" or " + denied_auth + " to cancel:");
    } else if (command == drop_command) {
        message.push_back("Do you want to remove this file from the standby stage?");
        message.push_back("The file in the standby stage is different from its original version.");
        message.push_back("This action can not be undone");

        options.push_back(confirmed_auth + " to autorize");
        options.push_back(" or " + denied_auth + " to cancel:");
    } else if (command == get_command) {
        message.push_back("Do you want to bring the previously saved versions of the files mentioned above?");
        message.push_back("You can keep the original files and bring the saved files with a compound name.");
        message.push_back("Therefore there would be no conflicts between both versions, Example of compound name: snapshotcode_name.");
        message.push_back("Or, you can replace the current files with the saved files, this option deletes the current files.");

        options.push_back(keep_auth + " to keep the current files");
        options.push_back(", " + replace_auth + " to replace the current files");
        options.push_back(" or " + denied_auth + " to cancel:");
    }

    for (const auto& row : message) {
        cout << row << endl;
    }

    cout << "Type ";
    for (const auto& row : options) {
        cout << row;
    }
    cout << endl;
}

Communicator::~Communicator() {}

