#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

// main
extern const std::string emi_path;
// database
extern const std::string db_path;
extern const std::string db_catch;
extern const std::string db_main;
extern const std::string db_temp;
// version
extern const std::string version_path;
extern const std::string version_main;
extern const std::string version_catch;
extern const std::string version_temp;
// config
extern const std::string config_path;
extern const std::string config_main;
extern const std::string config_ignore;
// commands
extern const std::string help_command;
extern const std::string version_command;
extern const std::string start_command;
extern const std::string catch_command;
extern const std::string snapshot_command;
extern const std::string look_command;
extern const std::string log_command;
extern const std::string ignore_command;
extern const std::string restart_command;
extern const std::string bye_command;
extern const std::string drop_command;
extern const std::string return_command;
// authorizathion
extern const std::string confirmed_auth;
extern const std::string denied_auth;
// group mode
extern const std::string process_all;

#endif // GLOBAL_H

