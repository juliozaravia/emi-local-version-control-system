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
	std::string current_path = fs::current_path().string();
	std::vector<std::string> arg_container;
	int validation_result = 0;
    
	Starter starter(current_path, argc, argv);
	starter.input_formatter(arg_container);
	starter.startup_validator(validation_result);

	Communicator printer;
	Manager manager(current_path, arg_container);
	if (validation_result == validation_codes::emi_and_path_valid) {
		if (arg_container.size() == 2) {
			if (arg_container[1] == help_command) {
				printer.command_reporter();
			} else if (arg_container[1] == version_command) {
				printer.version_reporter();
			} else if (arg_container[1] == start_command) {
				printer.event_reporter(warning_codes::emi_repository_exists);
			} else if (arg_container[1] == look_command) {
				try {
					manager.look_manager();
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, look_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, look_command, err.what());
				}
			} else if (arg_container[1] == log_command) {
				try {
					manager.log_manager();
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, log_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, log_command, err.what());
				}
			} else if (arg_container[1] == restart_command) {
				try {
					manager.restart_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::emi_directories_not_created, start_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(error_codes::emi_files_not_created, start_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, start_command, err.what());
				}
			} else if (arg_container[1] == bye_command) {
				try {
					manager.bye_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::emi_directories_not_created, start_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, start_command, err.what());
				}
			} else {
				printer.event_reporter(warning_codes::unknown_command);
			}
		} else if (arg_container.size() == 3) {
			if (arg_container[1] == catch_command) {
				try {
					manager.catch_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::unsuccessful_file_manipulation, catch_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, catch_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, catch_command, err.what());
				}
			} else if (arg_container[1] == ignore_command) {
				try {
					manager.ignore_manager();
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, ignore_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, ignore_command, err.what());
				}
			} else if (arg_container[1] == snapshot_command) {
				try {
					manager.snapshot_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::unsuccessful_file_manipulation, snapshot_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, snapshot_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, snapshot_command, err.what());
				}
			} else if (arg_container[1] == drop_command) {
				try {
					manager.drop_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::unsuccessful_file_manipulation, drop_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, drop_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, drop_command, err.what());
				}
			} else if (arg_container[1] == return_command) {
				try {
					manager.return_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::unsuccessful_file_manipulation, return_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(warning_codes::file_not_open, return_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, return_command, err.what());
				}
			} else {
				printer.event_reporter(warning_codes::unknown_command);
			}
		} else {
			printer.event_reporter(warning_codes::wrong_amount_of_commands);
		}
	} else if (validation_result == validation_codes::emi_and_path_not_valid) {
		if (arg_container.size() == 2) {
			if (arg_container[1] == help_command) {
				printer.command_reporter();
			} else if (arg_container[1] == version_command) {
				printer.version_reporter();
			} else if (arg_container[1] == start_command) {
				try {
					manager.start_manager();
				} catch (const fs::filesystem_error& err) {
					printer.event_reporter(error_codes::emi_directories_not_created, start_command, err.what());
				} catch (const std::ios_base::failure& err) {
					printer.event_reporter(error_codes::emi_files_not_created, start_command, err.what());
				} catch (const std::exception& err) {
					printer.event_reporter(error_codes::emi_unknown_error, start_command, err.what());
				}
			} else {
				printer.event_reporter(warning_codes::emi_repository_not_exists);
			}
		} else {
			printer.event_reporter(warning_codes::emi_repository_not_exists);
		}
	} else if (validation_result == validation_codes::emi_valid_path_not_valid) {
		if (arg_container.size() == 2) {
			if (arg_container[1] == help_command) {
				printer.command_reporter();
			} else if (arg_container[1] == version_command) {
				printer.version_reporter();
			} else {
				printer.event_reporter(warning_codes::parent_emi_repository_exists);
			}
		} else {
			printer.event_reporter(warning_codes::parent_emi_repository_exists);
		}
	}

	return 0;
}

