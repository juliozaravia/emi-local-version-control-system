/*
 * Project: EMI Personal Control Version System 
 * File: Main Class
 *
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <filesystem>
#include <string>
#include <vector>

#include "../include/Starter.h"
#include "../include/Manager.h"
#include "../include/Communicator.h"
#include "../include/Global.h"
#include "../include/Codes.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // We declare the initial variables that will be filled with data through the formatting and validation functions.
    // Note: We use the filesystem library to capture the current path and transform it into a text string.
    std::string current_path = fs::current_path().string();
    std::vector<std::string> arg_container;
    int validation_result = 0;

    // We create (initialize) the "starter" object to execute the previously mentioned operations.
    // We feed the functions with the necessary variables.
    Starter starter(current_path, argc, argv);
    starter.input_formatter(arg_container);

    // We create (initialize) the "printer" object to display success, warning or error messages as appropriate.
    // For the specific cases of the "--help" command and the "--version" command, the emi repository will not be validated...
    // ... because these commands are informative and available without creating a repository.
    Communicator printer;
    std::string command = arg_container.at(1);
    if ((command == help_command) || (command == version_command)) {
        if (arg_container.size() == 2) {
            if (command == help_command) {
                printer.command_reporter();
            } else if (command == version_command) {
                printer.version_reporter();
            } 
            return 0;
        } else {
            printer.warning_reporter(warning_codes::wrong_amount_of_commands);
            return 0;
        }
    }

    // We check that the command has been executed from a valid path.
    starter.startup_validator(validation_result);
    // We create (initialize) the "manager" object that will allow us to control the activities triggered by the command entered.
    Manager manager(current_path, arg_container);
    // We verify, according to the command entered, that we are on a valid path.
    // Additionally, we validate that the command has been written correctly and with the required number of arguments.
    // Each of the eventualities / problems / errors encountered when applying the entered command will be caught by a try / catch block.
    // This block will print the respective error for the user to read.
    if (validation_result == validation_codes::emi_and_path_valid) {
        if (arg_container.size() == 2) {
            if (command == start_command) {
                printer.warning_reporter(warning_codes::emi_repository_exists);
            } else if (command == look_command) {
                try {
                    manager.look_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, look_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, look_command, err.what());
                }
            } else if (command == log_command) {
                try {
                    manager.log_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, log_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, log_command, err.what());
                }
            } else if (command == restart_command) {
                try {
                    manager.restart_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, restart_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, restart_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, restart_command, err.what());
                }
            } else if (command == bye_command) {
                try {
                    manager.bye_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, bye_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, bye_command, err.what());
                }
            } else {
                printer.warning_reporter(warning_codes::unknown_command);
            }
        } else if (arg_container.size() == 3) {
            if (command == catch_command) {
                try {
                    manager.catch_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, catch_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, catch_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, catch_command, err.what());
                }
            } else if (command == ignore_command) {
                try {
                    manager.ignore_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, ignore_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, ignore_command, err.what());
                }
            } else if (command == snapshot_command) {
                try {
                    manager.snapshot_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, snapshot_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, snapshot_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, snapshot_command, err.what());
                }
            } else if (command == drop_command) {
                try {
                    manager.drop_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, drop_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, drop_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, drop_command, err.what());
                }
            } else if (command == get_command) {
                try {
                    manager.get_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, get_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_open_files, get_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, get_command, err.what());
                }
            } else {
                printer.warning_reporter(warning_codes::unknown_command);
            }
        } else {
            printer.warning_reporter(warning_codes::wrong_amount_of_commands);
        }
    } else if (validation_result == validation_codes::emi_and_path_not_valid) {
        if (arg_container.size() == 2) {
            if (command == start_command) {
                try {
                    manager.start_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, start_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.error_reporter(error_codes::unable_to_manipulate_files_or_directories, start_command, err.what());
                } catch (const std::exception& err) {
                    printer.error_reporter(error_codes::emi_unknown_error, start_command, err.what());
                }
            } else {
                printer.warning_reporter(warning_codes::emi_repository_not_exists);
            }
        } else {
            printer.warning_reporter(warning_codes::emi_repository_not_exists);
        }
    } else if (validation_result == validation_codes::emi_valid_path_not_valid) {
        printer.warning_reporter(warning_codes::parent_emi_repository_exists);
    }

    return 0;
}

