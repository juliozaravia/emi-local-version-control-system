/*
 * Project: EMI Personal Control Version System 
 * File: Structures file 
 *
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>

// Estructura que contiene todas las rutas necesarias para trabajar con el repositorio emi y sus archivos internos
struct Base {
    std::string emi_default_path;
    std::string config_default_path;
    std::string db_default_path;
    std::string version_default_path;
    std::string config_main_file;
    std::string config_ignore_file;
    std::string db_catch_file;
    std::string db_main_file;
    std::string db_temp_file;
    std::string version_catch_path;
    std::string version_main_path;
    std::string version_temp_path;
};

// Estructura que contiene todos los campos necesarios para capturar o guardar la versión del archivo respectivo
struct File {
    std:: string file = "null";
    unsigned file_hash = 0;
    std::string file_path = "null";
    unsigned int file_path_hash = 0;
    std::string version = "null";
    std::string version_name = "null";
    std::string file_name = "null";
    std::string file_extension = "null";
    std::string catch_date = "null";
    unsigned int snap_hash = 0;
    std::string snap_version = "null";
    std::string snap_date = "null";
    std::string comment = "null";
};

// Estructura complementaria a la interior
struct Log {
    std::string snapshot_code;
    std::string snapshot_date;
    std::string snapshot_comment;
};

#endif // STRUCTURES_H

