/*
 * Project: EMI Personal Control Version System 
 * File: Global file - Implementation 
 * Description: Clase de apoyo de recursos. Nos permite tener disponibles de manera global
 * todas las variables necesarias para ejecutar las operaciones solicitadas por el usuario 
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <string>

#include "../include/Global.h"

// General
const std::string emi_path = "emi_base";
// Database
const std::string db_path = "emi_database";
const std::string db_catch = "emi_catch_db.csv";
const std::string db_main = "emi_main_db.csv";
const std::string db_temp = "emi_temp_db.csv";
// Version
const std::string version_path = "emi_version";
const std::string version_main = "emi_main_version";
const std::string version_catch = "emi_catch_version";
const std::string version_temp = "emi_temp_version";
// Configuration
const std::string config_path = "emi_config";
const std::string config_main = "emi_config.txt";
const std::string config_ignore = "emi_ignore.txt";
// Commands
const std::string help_command = "--help";
const std::string version_command = "--version";
const std::string start_command = "-start";
const std::string catch_command = "-catch";
const std::string snapshot_command = "-snapshot";
const std::string look_command = "-look";
const std::string log_command = "-log";
const std::string ignore_command = "-ignore";
const std::string restart_command = "-restart";
const std::string bye_command = "-bye";
const std::string drop_command = "-drop";
const std::string get_command = "-get";
// Authorizathion
const std::string confirmed_auth = "YES";
const std::string denied_auth = "NO";
const std::string keep_auth = "KEEP";
const std::string replace_auth = "REPLACE";
// Group mode
const std::string process_all = "all";


