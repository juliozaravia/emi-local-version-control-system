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

// SE DEBE HCAER QUE EN CADA COPIA O MOVIMIENTO DE ARCHIVOS POR TEMAS DE SEGURIDAD EN PARALELO EXISTA UNA COPIA TEMPORAL MIENTRAS TODAS LAS ACTIVIDADES TERMINAN
// ASI PODEMOS RECURPERAR DE CUALQUIER PROBLEMA QUE SUCEDA EN CASO DE ERRORES.
// PENDIENTE TAMBIÉN AGREGAR FUNCIONALIDAD PARA SABER QUE HACER CUANDO ALGO DFALLA Y LAS CONSTRUCCUONES SE QUEDAN A MEDIAS.




// TAREA MENOR: VERIFICAR LOS MENSAJES DE ERROR DE LOS TRY/CATCH DE MAIN PARA CADA COMANDO, Y VER QUE CUADREN!!
// TAREA MENOR: VERIFICAR LOS MENSAJES DE ERROR DE LOS TRY/CATCH DE MAIN PARA CADA COMANDO, Y VER QUE CUADREN!!
// TAREA MENOR: VERIFICAR LOS MENSAJES DE ERROR DE LOS TRY/CATCH DE MAIN PARA CADA COMANDO, Y VER QUE CUADREN!!
// TAREA MENOR: VERIFICAR LOS MENSAJES DE ERROR DE LOS TRY/CATCH DE MAIN PARA CADA COMANDO, Y VER QUE CUADREN!!
// TAREA MENOR: VERIFICAR LOS MENSAJES DE ERROR DE LOS TRY/CATCH DE MAIN PARA CADA COMANDO, Y VER QUE CUADREN!!


// CONSTRUIR UN LOG DE ERRORES
// CONSTRUIR UN LOG DE ERRORES
// CONSTRUIR UN LOG DE ERRORES


// REVISAR REGLA DE 3 o de 5 PARA ONSTRUCTORES
// REVISAR REGLA DE 3 o de 5 PARA ONSTRUCTORES
// REVISAR REGLA DE 3 o de 5 PARA ONSTRUCTORES

// QUE PASA SI FALLA LA CREACION O ESCRITURA DE ARCIHVOS. PROGRAMAR UN RESTAURADOR
// QUE PASA SI FALLA LA CREACION O ESCRITURA DE ARCIHVOS. PROGRAMAR UN RESTAURADOR
// QUE PASA SI FALLA LA CREACION O ESCRITURA DE ARCIHVOS. PROGRAMAR UN RESTAURADOR
// QUE PASA SI FALLA LA CREACION O ESCRITURA DE ARCIHVOS. PROGRAMAR UN RESTAURADOR
// QUE PASA SI FALLA LA CREACION O ESCRITURA DE ARCIHVOS. PROGRAMAR UN RESTAURADOR

// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE
// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE
// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE
// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE
// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE
// QUE PASA SI EL COMMENT DEL SNAPSHOT ES DEMASIADO GRANDE

// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI
// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI
// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI
// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI
// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI
// QUE MASA SI EN EL COMMENT DEL SNAPSHOT PONGO ALGO SIN COMILLAS O UNA RUTA O ALGO ASI

// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE
// VERIFICAR QUE TODOS LOS "CONTADORES" SE JUSTIFIQUEN CON UNA CUENTA NUMERICA O NO SEAN UN BOOL, UN MEJOR APROACHE

// VERIFICAR QUE SE ESTEN SUANDO RUTAS COMPLETAS
// VERIFICAR QUE SE ESTEN SUANDO RUTAS COMPLETAS
// VERIFICAR QUE SE ESTEN SUANDO RUTAS COMPLETAS
// VERIFICAR QUE SE ESTEN SUANDO RUTAS COMPLETAS
// VERIFICAR QUE SE ESTEN SUANDO RUTAS COMPLETAS


// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION
// REVISAR LOS DATOS DEL DATA ORGANIZER PARA VER SI ESTA TRABAJANDO CON RUTAS COMPLETAS DE SER ASÍ SE PODRIA REDUCIR LA FUNCION

void Manager::start_manager() {
    Builder builder(base);
    builder.repository_builder(current_path);
    Communicator printer;
    printer.event_reporter(success_codes::emi_repository_created);
}

// Tested in Ubuntu
void Manager::catch_manager() {
    if (arg_container[2] == process_all) {
        multiple_catch_manager();
    } else {
        simple_catch_manager();
    }
}

// Tested in Ubuntu
void Manager::simple_catch_manager() {
    Communicator printer;
    Helper helper;
    bool file_exists = helper.existence_checker<string>(arg_container[2], current_path);
    if (file_exists) {
        bool file_is_ignored = helper.ignored_file_checker(arg_container[2], base.config_ignore_file);
        if (!file_is_ignored) {
            File data;
            helper.data_organizer(data, arg_container[2]);
            Builder builder;
            string catch_row = helper.row_extractor(data.file, base.db_catch_file);
            if (catch_row.empty()) {
                string main_row = helper.row_extractor(data.file, base.db_main_file);
                if (main_row.empty()) {
                    helper.timepoint_generator(data.catch_date);
                    builder.data_catcher<File>(data, base.db_catch_file, base.version_catch_path);
                    printer.event_reporter(success_codes::version_catched);
                } else {
                    vector<string> main_row_items;
                    helper.items_extractor(main_row_items, main_row);
                    bool is_same_hash = helper.hash_comparator(main_row_items, data);
                    if (is_same_hash) {
                        printer.event_reporter(warning_codes::identical_version_saved);
                    } else {
                        helper.timepoint_generator(data.catch_date);
                        builder.data_catcher<File>(data, base.db_catch_file, base.version_catch_path);
                        printer.event_reporter(success_codes::version_catched);
                    }
                }
            } else {
                vector<string> catch_row_items;
                helper.items_extractor(catch_row_items, catch_row);
                bool is_same_hash = helper.hash_comparator(catch_row_items, data);
                if (is_same_hash) {
                    printer.event_reporter(warning_codes::identical_version_in_standby);
                } else {
                    vector<string> protected_rows;
                    helper.rows_extractor(protected_rows, base.db_catch_file, catch_row);
                    helper.timepoint_generator(data.catch_date);
                    builder.file_remover<vector<string>>(catch_row_items, base.version_catch_path);
                    builder.data_cleaner(base.db_catch_file);
                    builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);
                    builder.data_catcher<File>(data, base.db_catch_file, base.version_catch_path);
                    printer.event_reporter(success_codes::version_catched);
                }
            }
        } else {
            printer.event_reporter(warning_codes::file_already_ignored, catch_command);
        }
    } else {
        printer.event_reporter(warning_codes::file_not_found);
    }
}

// Tested in Ubuntu
void Manager::multiple_catch_manager() {
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;

    Communicator printer;
    Helper helper;
    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);

    if (untracked_files.empty()) {
        printer.event_reporter(notification_codes::no_files_found, catch_command);
    } else {
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        vector<string> saved_modified;
        vector<string> saved_not_modified;

        vector<File> old_data;
        vector<File> catched_modified_data;
        vector<File> saved_modified_data;
        vector<File> untracked_data;

        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            helper.processed_files_organizer(catched_modified,
                    catched_not_modified,
                    modified_files,
                    standby_files,
                    base.db_catch_file);

            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                helper.processed_files_organizer(saved_modified,
                        saved_not_modified,
                        modified_files,
                        saved_files,
                        base.db_main_file);

                helper.data_organizer(old_data, catched_modified, action_mode::built);
                helper.data_organizer(catched_modified_data, catched_modified, action_mode::to_build);
                helper.data_organizer(saved_modified_data, saved_modified, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files);
            } else {
                helper.data_organizer(old_data, catched_modified, action_mode::built);
                helper.data_organizer(catched_modified_data, catched_modified, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files);
            }
        } else {
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                helper.processed_files_organizer(saved_modified,
                        saved_not_modified,
                        modified_files,
                        saved_files,
                        base.db_main_file);

                helper.data_organizer(saved_modified_data, saved_modified, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files);
            } else {
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files);
            }
        }

        Builder builder;
        if (!old_data.empty()) {
            builder.file_remover<vector<File>>(old_data, base.version_catch_path);
            builder.data_cleaner(base.db_catch_file);
        }
        if (!catched_not_modified.empty()) builder.data_inserter<vector<string>>(catched_not_modified, base.db_catch_file);
        if (!catched_modified_data.empty()) builder.data_catcher<vector<File>>(catched_modified_data, base.db_catch_file, base.version_catch_path);
        if (!saved_modified_data.empty()) builder.data_catcher<vector<File>>(saved_modified_data, base.db_catch_file, base.version_catch_path);
        if (!untracked_data.empty()) builder.data_catcher<vector<File>>(untracked_data, base.db_catch_file, base.version_catch_path);
        printer.event_reporter(success_codes::version_catched);
    }
}

void Manager::drop_manager() {
    if (arg_container[2] == process_all) {
        multiple_drop_manager();
    } else {
        simple_drop_manager();
    }
}

// Tested in Ubuntu
void Manager::simple_drop_manager() {
    Helper helper;
    Communicator printer;
    bool file_exists = helper.existence_checker<string>(arg_container[2], current_path);
    if (file_exists) {
        File data;
        helper.data_organizer(data, arg_container[2]);
        string catch_row = helper.row_extractor(data.file, base.db_catch_file);
        if (catch_row.empty()) {
            printer.event_reporter(warning_codes::file_not_catched, drop_command);
        } else {
            vector<string> protected_rows;
            helper.rows_extractor(protected_rows, base.db_catch_file, catch_row);
            vector<string> catch_row_items;
            helper.items_extractor(catch_row_items, catch_row);
            Builder builder;

            bool is_same_hash = helper.hash_comparator(catch_row_items, data);
            if (is_same_hash) {
                builder.file_remover<vector<string>>(catch_row_items, base.version_catch_path);
                builder.data_cleaner(base.db_catch_file);
                builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);
                printer.event_reporter(success_codes::version_dropped);
            } else {
                printer.authorization_reporter(drop_command);

                string authorization;
                std::cin >> authorization;
                if (authorization == confirmed_auth) {
                    builder.file_remover<vector<string>>(catch_row_items, base.version_catch_path);
                    builder.data_cleaner(base.db_catch_file);
                    builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);
                    printer.event_reporter(success_codes::version_dropped);
                } else if (authorization == denied_auth) {
                    printer.event_reporter(notification_codes::cancelled_action, drop_command);
                } else {
                    printer.event_reporter(warning_codes::unknown_authorization);
                }
            }
        }
    } else {
        printer.event_reporter(warning_codes::file_not_found);
    }
}

// Tested in Ubuntu
void Manager::multiple_drop_manager() {
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> catched_files;
    Helper helper;
    Communicator printer;

    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    // REVISAR multuple catch... porq aqui no hay condicional en caso se haga drop sin tener ningun archivo o solo ignores
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        helper.status_organizer(untracked_files, modified_files, catched_files, base.db_catch_file);
        helper.processed_files_organizer(catched_modified,
                catched_not_modified,
                modified_files,
                catched_files,
                base.db_catch_file);

        Builder builder;	
        if (catched_modified.empty()) {
            vector<File> catched_not_modified_data;
            helper.data_organizer(catched_not_modified_data, catched_not_modified, action_mode::built);
            if (!catched_not_modified_data.empty()) {
                //builder.version_cleaner(catched_not_modified_data);
                builder.file_remover<vector<File>>(catched_not_modified_data, base.version_catch_path);
                builder.data_cleaner(base.db_catch_file);
            }
        } else {
            printer.authorization_reporter(drop_command);
            string authorization;
            std::cin >> authorization;
            if (authorization == confirmed_auth) {
                vector<File> catched_modified_data;
                vector<File> catched_not_modified_data;
                helper.data_organizer(catched_modified_data, catched_modified, action_mode::built);
                helper.data_organizer(catched_not_modified_data, catched_not_modified, action_mode::built);
                if (!catched_modified_data.empty()) {
                    //builder.version_cleaner(catched_modified_data);
                    builder.file_remover<vector<File>>(catched_modified_data, base.version_catch_path);
                    builder.data_cleaner(base.db_catch_file);
                }
                if (!catched_not_modified_data.empty()) {
                    //builder.version_cleaner(catched_not_modified_data);
                    builder.file_remover<vector<File>>(catched_not_modified_data, base.version_catch_path);
                    builder.data_cleaner(base.db_catch_file);
                }
                printer.event_reporter(success_codes::version_dropped);
            } else if (authorization == denied_auth) {
                printer.event_reporter(notification_codes::cancelled_action, drop_command);
            } else {
                printer.event_reporter(warning_codes::unknown_authorization);
            }
        }
    } else {
        printer.event_reporter(warning_codes::no_files_to_save, drop_command);
    }
}

// Tested in Ubuntu
void Manager::snapshot_manager() {
    Communicator printer;
    Helper helper;
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        vector<string> version_names;
        helper.items_extractor(version_names, base.db_catch_file, db_pos::version_name);
        bool versions_exist = helper.existence_checker<vector<string>>(version_names, base.version_catch_path);
        if (versions_exist) {
            Builder builder;
            string timepoint;
            vector<string> catch_file_rows;
            helper.rows_extractor(catch_file_rows, base.db_catch_file);
            helper.timepoint_generator(timepoint);
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ACA HOYYYYYYYYYYYY 12:00
            // ESto no está del todo boien, se está usando una ruta para una carpeta de tipo version_ZZZZ_path dentro de otra carpeta del
            // mismo tipo, este version_temp deberia ser asignado dentro de la funcion quizá con un control enum
            // Esto puede ayudar a estandarizar el file_transporter
            // Esto puede ayudar a estandarizar el file_transporter
            // Esto puede ayudar a estandarizar el file_transporter
            // Esto puede ayudar a estandarizar el file_transporter
            // Esto puede ayudar a estandarizar el file_transporter
            // Esto puede ayudar a estandarizar el file_transporter
            builder.file_transporter(version_names, base.version_catch_path, base.version_main_path, version_temp);
            builder.data_cleaner(base.db_catch_file);
            builder.file_renamer(timepoint, base.version_main_path, version_temp);
            builder.data_saver(catch_file_rows, base.db_main_file, timepoint, arg_container[2]);
            printer.event_reporter(success_codes::version_saved);
        } else {
            printer.event_reporter(error_codes::inconsistency_detected, snapshot_command);
        }
    } else {
        printer.event_reporter(warning_codes::no_files_to_save);
    }
}

//Tested in Ubuntu
void Manager::look_manager() {
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;

    vector<string> ignored_files_or_folders;
    Helper helper;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);

    Communicator printer;
    if (untracked_files.empty()) {
        printer.status_reporter(untracked_files, modified_files, standby_files);
    } else {
        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files);
            }
        } else {
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files);
            }
        }
    }
}

// Tested in Ubuntu
void Manager::log_manager() {
    Log log;
    vector<Log> log_info;
    unordered_multimap<string,string> saved_files;

    Helper helper;
    Communicator printer;
    bool main_has_data = helper.content_checker(base.db_main_file);
    if (main_has_data) {
        vector<string> main_file_rows;
        helper.rows_extractor(main_file_rows, base.db_main_file);
        helper.log_organizer(log, log_info, saved_files, main_file_rows);
        printer.log_reporter(log_info, saved_files);
    } else {
        printer.log_reporter(log_info, saved_files);
    }
}

// Tested in Ubuntu
void Manager::ignore_manager() {
    Communicator printer;
    Helper helper;
    bool file_exists = helper.existence_checker<string>(arg_container[2], current_path);
    if (file_exists) {
        string catch_row = helper.row_extractor(arg_container[2], base.db_catch_file);
        string main_row = helper.row_extractor(arg_container[2], base.db_main_file);
        if (catch_row.empty() && main_row.empty()) {
            bool file_or_folder_is_ignored = helper.ignored_file_checker(arg_container[2], base.config_ignore_file);
            if (file_or_folder_is_ignored) {
                printer.event_reporter(warning_codes::file_already_ignored, ignore_command);
            } else {
                Builder builder;
                builder.data_inserter<string>(arg_container[2], base.config_ignore_file);
                printer.event_reporter(success_codes::file_ignored);
            }        
        } else {
            printer.event_reporter(warning_codes::file_in_use, ignore_command);        
        }
    } else {
        printer.event_reporter(warning_codes::file_not_found);
    }
}

void Manager::return_manager() {
    Helper helper;
    //Verificar si hay datos en main
    bool main_has_data = helper.content_checker(base.db_main_file);
    //if (main_has_data) {
        vector<string> ignored_files_or_folders;
        helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
        //Excluir archivos ignorados de los archivos que serán movidos
        vector<string> available_files;
        vector<string> available_folders;
        helper.availability_organizer(available_files, available_folders, ignored_files_or_folders, current_path);
        // Para mover fisicamente los archivos y/o insertarlos en la base de datos temporal
        // necesito un data de tipo File para guardar su estructura
        
        vector<File> available_files_data;
        helper.data_organizer<vector<string>>(available_files_data, available_files);
        
        for (auto data : available_files_data) {
            std::cout << "data.file -> " << data.file << std::endl; 
            std::cout << "data.file_name -> " << data.file_name << std::endl; 
            std::cout << "data.file_path -> " << data.file_path << std::endl; 
            std::cout << "data.file_path_hash -> " << data.file_path_hash << std::endl; 
            std::cout << "......................................" << std::endl; 
        }

        Builder builder;
        builder.file_transporter(available_files_data, base.version_temp_path);
        builder.folder_remover(available_folders);
        builder.data_catcher<vector<File>>(available_files_data, base.db_temp_file, base.version_temp_path);
    //} else {
        //std::cout << "No tiene data" << std::endl;
    //}
}

//Tested in Ubuntu
void Manager::restart_manager() {
    Communicator printer;
    printer.authorization_reporter(restart_command);

    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder(base);
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        builder.repository_builder(current_path);
        printer.event_reporter(success_codes::emi_repository_restarted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, restart_command);
    } else {
        printer.event_reporter(warning_codes::unknown_authorization);
    }
}

// Tested in Ubuntu
void Manager::bye_manager() {
    Communicator printer;
    printer.authorization_reporter(bye_command);

    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder;
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        printer.event_reporter(success_codes::emi_repository_deleted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, bye_command);
    } else {
        printer.event_reporter(warning_codes::unknown_authorization);
    }
}

Manager::~Manager() {}
