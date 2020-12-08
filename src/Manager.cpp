/*
 * Project: EMI Control Version System 
 * File: Manager Class
 *
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

// Definimos el constructor y lo inicializamos.
// Construimos todas las rutas necesarias que serán usadas por la clase Manager y las clases adicionales
// Utilizamos la estructura "base" para almancenar las rutas
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


// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR
// LA CLASE BUILDER TIENE UN CONSTRUCTOR QUE USA LA DATA BASE; VER EN QUE CASOS SE DEBE LLAMAR

// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT
// REVISAR QUE SE HAYA USADO BUILDER(BASE) COMO CONSTRUCTOR PARA CASOS ESPECÍFICOS EN DONDE SE NECESITE BASE COMO EN EL SNAPSHOT

// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)
// VERIFICAR QUE TODAS LAS LLAMADAS A FUNCIONES QUE SEAN TEMPLATE T, CUENTEN CON SU IDENTIFICADOR EX: EXISTENCE_CHECKER<VECTOR<STRING>>(param1, param2)

// Función miembro: start_manager(). 
// Invocada a través del comando -start. 
// Ex: emi -start
void Manager::start_manager() {
    // Creamos (inicializamos) el objeto "builder" para poder crear el repositorio emi
    // Dentro del repositorio emi se encuentran las configuraciones, bases de datos y archivos que permitirán el rastreo y almacenamiento de versiones 
    Builder builder(base);
    builder.repository_builder(current_path);
    Communicator printer;
    printer.event_reporter(success_codes::emi_repository_created);
}

// Función miembro: catch_manager(). Invocada a través del comando -catch
// Según los parámetros enviados se debe determinar cuál de las sub-funciones será ejecutada
// Capturar versión de archivo individual: simple_catch_manager()
// Capturar versiones de archivos grupales: multiple_catch_manager()
void Manager::catch_manager() {
    if (arg_container[2] == process_all) {
        multiple_catch_manager();
    } else {
        simple_catch_manager();
    }
}

// Función miembro: simple_catch_manager(). 
// Invocada a través del comando -catch y asignando como parámetro adicional el archivo cuya versión será capturada. 
// Ex: emi -catch relative_folder/file.txt
void Manager::simple_catch_manager() {
    Communicator printer;
    Helper helper;
    // Construímos la ruta completa del archivo cuya versión será capturada
    string file = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // Validamos la existencia del archivo
    bool file_exists = helper.existence_checker<string>(file, status);
    if (file_exists) {
        // Validamos que el archivo no se encuentre registrado en la lista de archivos ignorados
        bool file_is_ignored = helper.ignored_file_checker(file, base.config_ignore_file);
        if (!file_is_ignored) {
            Builder builder;
            File data;
            // Construimos la estructura y la llenamos con la información necesaria para capturar la versión más reciente del archivo
            helper.data_organizer<File,string>(data, file, base.version_catch_path);
            // Buscamos el archivo que será procesado en la base de datos de versiones de archivos capturados
            // Esto se hace con la finalidad de determinar si una versión del archivo ya ha sido capturado
            string catch_row = helper.row_extractor(data.file, base.db_catch_file);
            if (catch_row.empty()) {
                // Buscamos el archivo que será procesado en la base de datos de versiones de archivos guardados
                // Esto se hace con la finalidad de determinar si una versión del archivo ya ha sido guardado
                string main_row = helper.row_extractor(data.file, base.db_main_file);
                if (main_row.empty()) {
                    // Transportamos la versión más reciente del archivo al folder de versiones de archivos capturados
                    // Registramos los datos de la versión más reciente del archivo en la base de datos de versiones de archivos capturados
                    builder.file_transporter<File>(data, base.version_catch_path);
                    builder.data_catcher<File>(data, base.db_catch_file);
                    printer.event_reporter(success_codes::version_catched);
                } else {
                    string temporal_file_hash;
                    // Extraemos el valor hash de la versión del archivo que está registrado en la base de datos de archivos guardados
                    // Comparamos el valor hash de la versión almacenada en la base de datos y el valor hash de la versión del archivo actual
                    helper.content_extractor<string,string>(temporal_file_hash, main_row, db_pos::file_hash);
                    bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
                    if (is_same_hash) {
                        printer.event_reporter(warning_codes::identical_version_saved);
                    } else {
                        // Transportamos la versión más reciente del archivo al folder de versiones de archivos capturados
                        // Registramos los datos de la versión más reciente del archivo en la base de datos de versiones de archivos capturados
                        builder.file_transporter<File>(data, base.version_catch_path);
                        builder.data_catcher<File>(data, base.db_catch_file);
                        printer.event_reporter(success_codes::version_catched);
                    }
                }
            } else {
                string temporal_file_hash;
                // Extraemos el valor hash de la versión del archivo que está registrado en la base de datos de archivos capturados
                // Comparamos el valor hash de la versión almacenada en la base de datos y el valor hash de la versión del archivo actual
                helper.content_extractor<string,string>(temporal_file_hash, catch_row, db_pos::file_hash);
                bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
                if (is_same_hash) {
                    printer.event_reporter(warning_codes::identical_version_in_standby);
                } else {
                    vector<string> protected_rows;
                    string temporal_version;
                    // Extraemos los registros de las versiones que no sean la versión del archivo que está siendo procesado
                    // Extraemos la ruta completa de la versión del archivo que está siendo procesado
                    helper.rows_extractor(protected_rows, base.db_catch_file, catch_row, action_mode::different_to_row);
                    helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                    // Debido a que el valor hash es diferente: Eliminamos la versión que se encuentra en el folder de archivos capturados
                    // Eliminamos el registro de la versión del archivo de la base de datos de versiones de archivos capturados
                    // Insertamos los registros extraídos anteriormente en la base de datos de archivos capturados
                    // Transportamos la versión más reciente del archivo al folder de versiones de archivos capturados
                    // Registramos los datos de la versión más reciente del archivo en la base de datos de versiones de archivos capturados
                    builder.file_remover<string>(temporal_version);
                    builder.data_cleaner(base.db_catch_file);
                    builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);
                    builder.file_transporter<File>(data, base.version_catch_path);
                    builder.data_catcher<File>(data, base.db_catch_file);
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

// Función miembro: multiple_catch_manager(). 
// Invocada a través del comando -catch y asignando como parámetro adicional el subcomando "all"
// Ex. emi -catch all
void Manager::multiple_catch_manager() {
    // Creamos los contenedores necesarios para almacenar la información de:
    // (1) untracked_files: Archivos que no tienen aún una versión capturada mediante el comando -catch
    // (2) modified_files: Archivos modificados de su versión más reciente (versión más reciente capturada o guardada)
    // (3) standby_files: Archivos que cuentan con una versión capturada y puesta en la etapa de standby mediante el comando -catch
    // (4) saved_files: Archivos que tienen una versión guardada mediante el comando -snapshot
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;

    Communicator printer;
    Helper helper;
    // Llenamos el contenedor "untracked_files únicamente con los archivos que no se encuentren registrados en la lista de archivos ignorados
    // Se guardará el valor hash de la versión más reciente del archivo, y, la ruta del archivo completo
    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // Validamos que existan archivos disponibles (Es decir, archivos que no hayan sido ignorados, capturados o guardados anteriormente)
    if (untracked_files.empty()) {
        printer.event_reporter(notification_codes::no_files_found, catch_command);
    } else {
        // Creamos los contenedores necesarios para procesar la información:
        // (1) catched_modified: Archivos que tengan una versión capturada pero que cuenten con una versión modificada más reciente
        // (2) catched_not_modified: Archivos cuya versión capturada sea la más reciente
        // (3) saved_modified: Archivos que tengan una versión guardada pero que cuenten con una versión modificada más reciente
        // (4) saved_not_modified: Archivos cuya versión guardada sea la más reciente
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        vector<string> saved_modified;
        vector<string> saved_not_modified;
        // Creamos los contenedores que serán llenados con la data procesada de los contenedores catched_modified, catched_not_modified, saved_modified y saved_not_modified  
        vector<File> old_data;
        vector<File> catched_modified_data;
        vector<File> saved_modified_data;
        vector<File> untracked_data;
        // Validamos si la base de datos de archivos capturados cuenta o no con información registrada previamente
        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
            // En este punto solo procesamos la data de la base de datos de versiones de archivos capturados
            // La base de datos de versiones de archivos guardados será analizada más adelante
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            // Llenamos los contenedores de tipo "vector" con la data procesada y almacenada en modified_files y standby_files 
            helper.processed_files_organizer(catched_modified, catched_not_modified, modified_files, standby_files, base.db_catch_file);
            // Validamos si la base de datos de archivos guardados cuenta o no con información registrada previamente
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
                // En este punto solo procesamos la data de la base de datos de versiones de archivos guardados
                // La base de datos de versiones de archivos capturados ya fue analizada previamente... 
                // ... por lo que esta actividad termina de construir completamente los contenedores
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                // Llenamos los contenedores de tipo "vector" con la data procesada y almacenada en modified_files y saved_files
                helper.processed_files_organizer(saved_modified, saved_not_modified, modified_files, saved_files, base.db_main_file);
                // LLenamos las estructuras declaradas anteriormente de la siguiente manera:
                // (1) old_data: Data de los archivos que cuenta con una versión ya capturada pero que no es la más reciente. 
                // Esta data es extraida de los registros de la base de datos de versiones de archivos capturados (action_mode::built) 
                // (2) catched_modified_data: Data de los archivos que cuentan con una versión ya capturada pero que no es la más reciente
                // Esta data es contruida en base a la nueva información del archivo (action_mode::to_build)
                // (3) saved_modified_data: Data de los archivos que cuentan con una versión ya guardada pero que no es la más reciente  
                // Esta data es contruida en base a la nueva información del archivo (action_mode::to_build)
                // (4) untracked_data: Data de los archivos que aún no han sido capturados o guardados
                helper.data_organizer<vector<File>,vector<string>>(old_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<vector<File>,vector<string>>(saved_modified_data, saved_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            } else {
                // LLenamos las estructuras declaradas anteriormente de la siguiente manera:
                // (1) old_data: Data de los archivos que cuenta con una versión ya capturada pero que no es la más reciente. 
                // Esta data es extraida de los registros de la base de datos de versiones de archivos capturados (action_mode::built) 
                // (2) catched_modified_data: Data de los archivos que cuentan con una versión ya capturada pero que no es la más reciente
                // Esta data es contruida en base a la nueva información del archivo (action_mode::to_build)
                // (3) untracked_data: Data de los archivos que aún no han sido capturados o guardados
                helper.data_organizer<vector<File>,vector<string>>(old_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            }
        } else {
            // Validamos si la base de datos de archivos guardados cuenta o no con información registrada previamente
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
                // En este punto solo procesamos la data de la base de datos de versiones de archivos guardados
                // La base de datos de versiones de archivos capturados no fue analizada debido a que está vacía  
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                // Llenamos los contenedores de tipo "vector" con la data procesada y almacenada en modified_files y saved_files
                helper.processed_files_organizer(saved_modified, saved_not_modified, modified_files, saved_files, base.db_main_file);
                // LLenamos las estructuras declaradas anteriormente de la siguiente manera:
                // (1) saved_modified_data: Data de los archivos que cuentan con una versión ya guardada pero que no es la más reciente  
                // Esta data es contruida en base a la nueva información del archivo (action_mode::to_build)
                // (2) untracked_data: Data de los archivos que aún no han sido capturados o guardados
                helper.data_organizer<vector<File>,vector<string>>(saved_modified_data, saved_modified, base.version_catch_path, action_mode::to_build);
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            } else {
                // LLenamos las estructuras declaradas anteriormente de la siguiente manera:
                // (1) untracked_data: Data de los archivos que aún no han sido capturados o guardados
                helper.data_organizer<unordered_map<string,string>>(untracked_data, untracked_files, base.version_catch_path);
            }
        }

        Builder builder;
        // Verificamos el estado de los contenedores. Un contenedor con data siempre debe ser procesado.
        if (!old_data.empty()) {
            // Eliminamos las versiones procesadas como capturadas, pero modificadas posteriormente
            // Eliminamos los registros de la base de datos de versiones de archivos capturados
            builder.file_remover<vector<File>>(old_data, db_pos::version);
            builder.data_cleaner(base.db_catch_file);
        }         
        if (!catched_not_modified.empty())  { 
            // Insertamos las versiones de los archivos ya capturados que no han sido modificados posteriormente en la DB de versiones de archivos capturados
            builder.data_inserter<vector<string>>(catched_not_modified, base.db_catch_file);
        }
        if (!catched_modified_data.empty()) {
            // Creamos una copia de las versiones más recientes de los archivos que han sido capturados y modificados posteriormente
            // Transportamos las copias de las versiones al folder contenedor de versiones capturadas
            // Registramos la data de las versiones en la base de datos de versiones de archivos capturados
            builder.file_transporter<vector<File>>(catched_modified_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(catched_modified_data, base.db_catch_file);
        }
        if (!saved_modified_data.empty()) { 
            // Creamos una copia de las versiones más recientes de los archivos que han sido guardados y modificados posteriormente
            // Transportamos las copias de las versiones al folder contenedor de versiones capturadas
            // Registramos la data de las versiones en la base de datos de versiones de archivos capturados
            builder.file_transporter<vector<File>>(saved_modified_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(saved_modified_data, base.db_catch_file);
        }
        if (!untracked_data.empty()) {
            // Creamos una copia de las versiones de los archivos que aún no han sido capturados o guardados
            // Transportamos las copias de las versiones al folder contenedor de versiones capturadas
            // Registramos la data de las versiones en la base de datos de versiones de archivos capturados
            builder.file_transporter<vector<File>>(untracked_data, base.version_catch_path);
            builder.data_catcher<vector<File>>(untracked_data, base.db_catch_file);
        }
        printer.event_reporter(success_codes::version_catched);
    }
}

// Función miembro: drop_manager(). Invocada a través del comando -drop
// Según los parámetros enviados se debe determinar cuál de las sub-funciones será ejecutada
// Remover versión de archivo individual en la fase de standby: simple_drop_manager()
// Remover todas las versiones de archivos en la fase de standby: multiple_drop_manager()
void Manager::drop_manager() {
    if (arg_container[2] == process_all) {
        multiple_drop_manager();
    } else {
        simple_drop_manager();
    }
}

// Función miembro: simple_drop_manager(). 
// Invocada a través del comando -drop y asignando como parámetro adicional el archivo cuya versión será removida. 
// Ex: emi -drop relative_folder/file.txt
void Manager::simple_drop_manager() {
    Helper helper;
    Communicator printer;
    // Construímos la ruta completa del archivo cuya versión será capturada
    string file = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // Validamos la existencia del archivo
    bool file_exists = helper.existence_checker<string>(file, status);
    if (file_exists) {
        File data;
        // Construimos la estructura y la llenamos con la información necesaria 
        // ***************** Pareciera que acá no es necesario crear un data en base a data_organizer, debido a que solo se usan
        // **************** el data.file y data.hash, esto facilmente se puede trabajar sin el data_organizar
        helper.data_organizer<File,string>(data, file, base.version_catch_path);
        // Buscamos el archivo que será procesado en la base de datos de versiones de archivos capturados
        // Esto se hace con la finalidad de determinar si el archivo aún no ha sido capturado
        string catch_row = helper.row_extractor(data.file, base.db_catch_file);
        if (catch_row.empty()) {
            printer.event_reporter(warning_codes::file_not_catched, drop_command);
        } else {
            Builder builder;
            // Extraemos todos los registros de la base de datos de archivos capturados... 
            // ...menos el registro correspondiente a la versión del archivo que deseamos remover
            vector<string> protected_rows;
            helper.rows_extractor(protected_rows, base.db_catch_file, catch_row, action_mode::different_to_row);
            // Extraemos el valor hash de la versión registrada en la base de datos de versiones de archivos capturados
            string temporal_file_hash;
            helper.content_extractor<string,string>(temporal_file_hash, catch_row, db_pos::file_hash);
            // Comparamos el valor hash de la versión construida (versión más reciente) con el valor hash extraido de la base de datos
            // Hacemos esto con la finalidad de determinar si el archivo fue modificado luego de haber sido capturado
            bool is_same_hash = helper.hash_comparator(temporal_file_hash, data.file_hash);
            if (is_same_hash) {
                // Extraemos la ruta completa de la versión que ha sido registrada en la base de datos de versiones de archivos capturados
                string temporal_version;
                helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                // Eliminamos la versión que se encuentra en el folder de versiones de archivos capturados
                // Eliminamos los registros de las versiones de los archivos de la base de datos de versiones de archivos capturados
                // Insertamos los registros extraídos anteriormente en la base de datos de archivos capturados
                builder.file_remover<string>(temporal_version);
                builder.data_cleaner(base.db_catch_file);
                builder.data_inserter<vector<string>>(protected_rows, base.db_catch_file);

                printer.event_reporter(success_codes::version_dropped);
            } else {
                // Solicitamos la autorización del usuario para continuar con las actividades 
                printer.authorization_reporter(drop_command);
                string authorization;
                std::cin >> authorization;
                if (authorization == confirmed_auth) {
                    // Extraemos la ruta completa de la versión que ha sido registrada en la base de datos de versiones de archivos capturados
                    string temporal_version;
                    helper.content_extractor<string,string>(temporal_version, catch_row, db_pos::version);
                    // Eliminamos la versión que se encuentra en el folder de versiones de archivos capturados
                    // Eliminamos los registros de las versiones de los archivos de la base de datos de versiones de archivos capturados
                    // Insertamos los registros extraídos anteriormente en la base de datos de archivos capturados
                    builder.file_remover<string>(temporal_version);
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

// Función miembro: multiple_drop_manager(). 
// Invocada a través del comando -drop y asignando como parámetro adicional el subcomando "all"
// Ex. emi -drop all
void Manager::multiple_drop_manager() {
    // Creamos los contenedores necesarios para almacenar la información de:
    // (1) untracked_files: Archivos que no tienen aún una versión capturada mediante el comando -catch
    // (2) modified_files: Archivos modificados de su versión más reciente (versión más reciente capturada o guardada)
    // (3) catched_files: Archivos que cuentan con una versión capturada y puesta en la etapa de standby mediante el comando -catch
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> catched_files;
    Helper helper;
    Communicator printer;
    // Llenamos el contenedor "untracked_files únicamente con los archivos que no se encuentren registrados en la lista de archivos ignorados
    // Se guardará el valor hash de la versión más reciente del archivo, y, la ruta del archivo completo
    // ********************REVISAR multuple catch... porq aqui no hay condicional en caso se haga drop sin tener ningun archivo o solo ignores
    // ******************** REVISAR estructura de multiple cathc para organizar similar
    vector<string> ignored_files_or_folders;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // Validamos si la base de datos de archivos capturados cuenta o no con información registrada previamente
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        Builder builder;	
        // Creamos los contenedores necesarios para procesar la información:
        // (1) catched_modified: Archivos que tengan una versión capturada pero que cuenten con una versión modificada más reciente
        // (2) catched_not_modified: Archivos cuya versión capturada sea la más reciente
        vector<string> catched_modified;
        vector<string> catched_not_modified;
        // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
        // En este punto solo procesamos la data de la base de datos de versiones de archivos capturados
        // La base de datos de versiones de archivos guardados será analizada más adelante
        helper.status_organizer(untracked_files, modified_files, catched_files, base.db_catch_file);
        // Llenamos los contenedores de tipo "vector" con la data procesada y almacenada en modified_files y standby_files 
        helper.processed_files_organizer(catched_modified, catched_not_modified, modified_files, catched_files, base.db_catch_file);
        // Validamos que existan versiones de archivos capturados que hayan sido modificados posteriormente
        if (catched_modified.empty()) {
            // LLenamos las estructuras declaradas de la siguiente manera:
            // (1) catched_not_modified_data: Data de los archivos que cuentan con una versión ya capturada que no ha sido modificada posteriormente
            // Esta data es extraida de los registros de la base de datos de versiones de archivos capturados (action_mode::built) 
            vector<File> catched_not_modified_data;
            helper.data_organizer<vector<File>,vector<string>>(catched_not_modified_data, catched_not_modified, base.version_catch_path, action_mode::built);
            // Verificamos el estado de los contenedores. Un contenedor con data siempre debe ser procesado.
            if (!catched_not_modified_data.empty()) {
                // Eliminamos las versiones procesadas como capturadas, pero no modificadas posteriormente
                // Eliminamos los registros de la base de datos de versiones de archivos capturados
                builder.file_remover<vector<File>>(catched_not_modified_data, db_pos::version);
                builder.data_cleaner(base.db_catch_file);
            }
            printer.event_reporter(success_codes::version_dropped);
        } else {
            // Solicitamos la autorización del usuario para continuar con las actividades
            printer.authorization_reporter(drop_command);
            string authorization;
            std::cin >> authorization;
            if (authorization == confirmed_auth) {
                // LLenamos las estructuras declaradas de la siguiente manera:
                // (1) catched_modified_data: Data de los archivos que cuentan con una versión ya capturada que ha sido modificada posteriormente
                // Esta data es extraida de los registros de la base de datos de versiones de archivos capturados (action_mode::built) 
                // (2) catched_not_modified_data: Data de los archivos que cuentan con una versión ya capturada que no ha sido modificada posteriormente
                // Esta data es extraida de los registros de la base de datos de versiones de archivos capturados (action_mode::built) 
                vector<File> catched_modified_data;
                vector<File> catched_not_modified_data;
                helper.data_organizer<vector<File>,vector<string>>(catched_modified_data, catched_modified, base.version_catch_path, action_mode::built);
                helper.data_organizer<vector<File>,vector<string>>(catched_not_modified_data, catched_not_modified, base.version_catch_path, action_mode::built);
                // Verificamos el estado de los contenedores. Un contenedor con data siempre debe ser procesado.
                if (!catched_modified_data.empty()) {
                    // Eliminamos la versión del archivo capturado y modificado posteriormente que se encuentra en el folder de versiones de archivos capturados
                    // Eliminamos los registros de las versiones de los archivos de la base de datos de versiones de archivos capturados
                    builder.file_remover<vector<File>>(catched_modified_data, db_pos::version);
                    builder.data_cleaner(base.db_catch_file);
                }
                if (!catched_not_modified_data.empty()) {
                    // Eliminamos la versión del archivo capturado que se encuentra en el folder de versiones de archivos capturados
                    // Eliminamos los registros de las versiones de los archivos de la base de datos de versiones de archivos capturados
                    builder.file_remover<vector<File>>(catched_not_modified_data, db_pos::version);
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

// Función miembro: snapshot_manager(). 
// Invocada a través del comando -snapshot y asignando como parámetro adicional un mensaje descriptivo de la(s) versión(es) guardada(s)
// Ex. emi -snapshot "Este es un comentario descriptivo"
void Manager::snapshot_manager() {
    Communicator printer;
    Helper helper;
    // Validamos si la base de datos de archivos capturados cuenta o no con información registrada previamente
    bool catch_has_data = helper.content_checker(base.db_catch_file);
    if (catch_has_data) {
        // Extraemos las rutas completas de las versiones de los archivos capturados
        vector<string> version_names;
        helper.content_extractor<vector<string>,string>(version_names, base.db_catch_file, db_pos::version);
        // Verificamos que las rutas de las versiones de los archivos capturados sean correctas y los archivos existan
        unordered_map<string,bool> status;
        bool versions_exist = helper.existence_checker<vector<string>>(version_names, status);
        if (versions_exist) {
            Builder builder(base);
            string timepoint;
            vector<string> catch_file_rows;
            // Extraemos todos los registros de la base de datos de versiones de archivos capturados
            helper.rows_extractor(catch_file_rows, base.db_catch_file);
            // Capturamos la hora exacta en la que el proceso se está ejecutando
            // Generamos un valor hash único utilizando el time point anterior
            helper.timepoint_generator(timepoint);
            unsigned int timepoint_hash = helper.hash_generator(timepoint, action_mode::simple);
            // Transportamos una copia de las versiones almacenadas en el folder de versiones de archivos capturados...
            // ...hacia una sub-carpeta temporal dentro del folder de versiones de archivos guardados
            // Eliminamos las versiones de los archivos capturados
            builder.file_transporter<vector<string>>(version_names, base.version_main_path, version_temp);
            // Eliminamos las versiones de los archivos capturados
            builder.file_remover<vector<string>>(version_names);
            // Eliminamos los registros de la base de datos de versiones de archivos capturados
            builder.data_cleaner(base.db_catch_file);
            // Renombramos la sub-carpeta temporal creada dentro del folder de versiones de archivos guardados
            // El nuevo nombre del folder será el valor hash creado anteriormente
            builder.file_renamer(std::to_string(timepoint_hash), base.version_main_path, version_temp);
            // Guardamos los registros extraídos de la base de datos de versiones de archivos capturados... 
            // ...en la base de datos de versiones de archivos guardados
            // Adicionalmente se registran valores adicionales necesarios para que la data sea guardada correctamente
            // Estos valores adicionales son: valor hash identificador, hora de ejecución y comentario
            builder.data_saver(catch_file_rows, base.db_main_file, timepoint, std::to_string(timepoint_hash), arg_container[2]);
            printer.event_reporter(success_codes::version_saved);
        } else {
            printer.event_reporter(error_codes::inconsistency_detected, snapshot_command);
        }
    } else {
        printer.event_reporter(warning_codes::no_files_to_save);
    }
}

// Función miembro: look_manager(). 
// Invocada a través del comando -look. 
// Ex. emi -look 
void Manager::look_manager() {
    // Creamos los contenedores necesarios para almacenar la información de:
    // (1) untracked_files: Archivos que no tienen aún una versión capturada mediante el comando -catch
    // (2) modified_files: Archivos modificados de su versión más reciente (versión más reciente capturada o guardada)
    // (3) standby_files: Archivos que cuentan con una versión capturada y puesta en la etapa de standby mediante el comando -catch
    // (4) saved_files: Archivos que tienen una versión guardada mediante el comando -snapshot
    unordered_map<string,string> untracked_files;
    unordered_map<string,string> modified_files;
    unordered_map<string,string> standby_files;
    unordered_map<string,string> saved_files;
    // Llenamos el contenedor "untracked_files únicamente con los archivos que no se encuentren registrados en la lista de archivos ignorados
    // Se guardará el valor hash de la versión más reciente del archivo, y, la ruta del archivo completo
    vector<string> ignored_files_or_folders;
    Helper helper;
    helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);
    helper.availability_organizer(untracked_files, ignored_files_or_folders, current_path);
    // Validamos que existan archivos disponibles (Es decir, archivos que no hayan sido ignorados, capturados o guardados anteriormente)
    Communicator printer;
    if (untracked_files.empty()) {
        printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
    } else {
        // Validamos si la base de datos de archivos capturados cuenta o no con información registrada previamente
        bool catch_has_data = helper.content_checker(base.db_catch_file);
        if (catch_has_data) {
            // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
            // En este punto solo procesamos la data de la base de datos de versiones de archivos capturados
            // La base de datos de versiones de archivos guardados será analizada más adelante
            helper.status_organizer(untracked_files, modified_files, standby_files, base.db_catch_file);
            // Validamos si la base de datos de archivos guardados cuenta o no con información registrada previamente
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
                // En este punto solo procesamos la data de la base de datos de versiones de archivos guardados
                // La base de datos de versiones de archivos capturados ya fue analizada previamente... 
                // ... por lo que esta actividad termina de construir completamente los contenedores
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            }
        } else {
            // Validamos si la base de datos de archivos guardados cuenta o no con información registrada previamente
            bool main_has_data = helper.content_checker(base.db_main_file);
            if (main_has_data) {
                // LLenamos los contenedores de tipo "unordered_map" con la información respectiva
                // En este punto solo procesamos la data de la base de datos de versiones de archivos guardados
                // La base de datos de versiones de archivos capturados no fue analizada debido a que está vacía  
                helper.status_organizer(untracked_files, modified_files, saved_files, base.db_main_file);
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            } else {
                printer.status_reporter(untracked_files, modified_files, standby_files, current_path);
            }
        }
    }
}

// Función miembro: log_manager(). 
// Invocada a través del comando -log. 
// Ex. emi -log 
void Manager::log_manager() {
    Log log;
    // Creamos los contenedores necesarios para almacenar la información de:
    // (1) log_info: Estructura que contiene la data generada al momento de aplicar el -snapshot...
    // ...Esta data es: Snapshot code (hash value), fecha de snapshot y comentario
    // (2) saved_files: Archivos cuyas versiones han sido guardadas. Cada archivo está asociado al valor hash único generado al momento de aplicar -snapshot 
    vector<Log> log_info;
    unordered_multimap<string,string> saved_files;

    Helper helper;
    Communicator printer;
    // Validamos si la base de datos de archivos guardados cuenta o no con información registrada previamente
    bool main_has_data = helper.content_checker(base.db_main_file);
    if (main_has_data) {
        // Extraemos todos los registros de la base de datos de versiones de archivos guardados 
        vector<string> main_file_rows;
        helper.rows_extractor(main_file_rows, base.db_main_file);
        // Llenamos los contenedores en base a los registros extraídos de la base de datos de versiones de archivos guardados
        helper.log_organizer(log, log_info, saved_files, main_file_rows);
        // Enviamos los contenedores con la información necesaria a la función que imprimirá los resultados
        printer.log_reporter(log_info, saved_files, current_path);
    } else {
        // Enviamos los contenedores con la información necesaria a la función que imprimirá los resultados,
        // En este caso los contenedores irán vacíos por lo que se informará al usuario que no existen registros
        printer.log_reporter(log_info, saved_files, current_path);
    }
}

// Función miembro: ignore_manager(). 
// Invocada a través del comando -ignore y asignando como parámetro adicional el archivo que será ignorado. 
// Ex: emi -ignore relative_folder/file.txt
void Manager::ignore_manager() {
    Communicator printer;
    Helper helper;
    // Construímos la ruta completa del archivo cuya versión será utilizada
    string file_or_folder = helper.location_generator(arg_container[2], current_path);
    unordered_map<string,bool> status;
    // Validamos la existencia del archivo
    bool file_exists = helper.existence_checker<string>(file_or_folder, status);
    if (file_exists) {
        // Buscamos el archivo que será procesado en la base de datos de versiones de archivos capturados y guardados
        // Esto se hace con la finalidad de determinar si el archivo aún no ha sido previamente capturado o guardado
        string catch_row = helper.row_extractor(file_or_folder, base.db_catch_file);
        string main_row = helper.row_extractor(file_or_folder, base.db_main_file);
        if (catch_row.empty() && main_row.empty()) {
            // Validamos que el archivo no se encuentre registrado en la lista de archivos ignorados
            bool file_or_folder_is_ignored = helper.ignored_file_checker(file_or_folder, base.config_ignore_file);
            if (file_or_folder_is_ignored) {
                printer.event_reporter(warning_codes::file_already_ignored, ignore_command);
            } else {
                Builder builder;
                // Insertamos la ruta completa del archivo en el archivo de ignorados. 
                builder.data_inserter<string>(file_or_folder, base.config_ignore_file);
                printer.event_reporter(success_codes::file_ignored);
            }        
        } else {
            printer.event_reporter(warning_codes::file_in_use, ignore_command);        
        }
    } else {
        printer.event_reporter(warning_codes::file_not_found);
    }
}

void Manager::get_manager() {
    Communicator printer;
    Helper helper;

    bool main_has_data = helper.content_checker(base.db_main_file);

    string snapshot_code = arg_container[2];
    string target_directory = helper.location_generator(arg_container[2], current_path);
    vector<string> main_file_rows;
    helper.rows_extractor(main_file_rows, base.db_main_file, snapshot_code, action_mode::similar_to_item, db_pos::snap_hash);

    if (main_file_rows.empty()) {
        std::cout << "tu codigo hash no existe en main, revisa bien con log" << std::endl;
    } else {
        Builder builder;
        vector<string> main_version_names;
        helper.content_extractor(main_version_names, main_file_rows, db_pos::snap_version);

        printer.authorization_reporter(get_command);
        string authorization;
        std::cin >> authorization;
        if (authorization == keep_auth) {
            builder.directory_builder<string>(target_directory);
            builder.file_transporter<vector<string>>(main_version_names, target_directory);
            printer.event_reporter(success_codes::version_restored);
        } else if (authorization == replace_auth) {
            vector<string> path_names;
            helper.content_extractor(path_names, main_file_rows, db_pos::path_name);
            vector<string> file_names;
            helper.content_extractor(file_names, main_file_rows, db_pos::file);

            helper.duplicate_organizer(path_names);
            unordered_map<string,bool> directories_and_status;
            helper.existence_checker<vector<string>>(path_names, directories_and_status);
            unordered_map<string,bool> files_and_status;
            helper.existence_checker<vector<string>>(file_names, files_and_status);

            builder.file_remover<unordered_map<string,bool>>(files_and_status);
            builder.directory_builder<unordered_map<string,bool>>(directories_and_status);
            builder.special_transporter(main_version_names, file_names);
            printer.event_reporter(success_codes::version_restored);
        } else if (authorization == denied_auth) {
            printer.event_reporter(notification_codes::cancelled_action, get_command);
        } else {
            printer.event_reporter(warning_codes::unknown_authorization);
        }
    }


    /*string authorization;
      std::cin >> authorization;
      if (authorization == keep_auth) {*/

    /*vector<string> ignored_files_or_folders;
      helper.rows_extractor(ignored_files_or_folders, base.config_ignore_file);

      vector<string> available_files;
      vector<string> available_folders;
      helper.availability_organizer(available_files, available_folders, ignored_files_or_folders, current_path);

      vector<File> available_files_data;
      helper.data_organizer<vector<string>>(available_files_data, available_files, base.version_catch_path);

      vector<string> version_names; 
      helper.content_extractor<vector<string>,string>(version_names, base.db_catch_file, db_pos::version);

      Builder builder;
      builder.file_transporter<vector<File>>(available_files_data, base.version_temp_path);
      builder.file_remover<vector<File>>(available_files_data, db_pos::file);
      builder.folder_remover(available_folders);
      builder.data_catcher<vector<File>>(available_files_data, base.db_temp_file);

      builder.file_remover<vector<string>>(version_names);
      builder.data_cleaner(base.db_catch_file);*/

    /* ACA ES LO BUENO
       string snapshot_code = arg_container[2];
       vector<string> rows_of_main;
       helper.rows_extractor(rows_of_main, base.db_main_file, snapshot_code, action_mode::similar_to_item, db_pos::snap_hash);

       for (auto item : rows_of_main) {
       std::cout << "item -> " << item << std::endl;
       }

       vector<string> rutas;
       helper.content_extractor(rutas, rows_of_main, db_pos::path_name);

       for (auto item : rutas) {
       std::cout << "item ruta -> " << item << std::endl;
       }

       vector<string> archivos;
       helper.content_extractor(archivos, rows_of_main, db_pos::file);

       for (auto item : archivos) {
       std::cout << "item archivo -> " << item << std::endl;
       }*/



    /*} else if (authorization == denied_auth) {
      printer.event_reporter(notification_codes::cancelled_action, get_command);
      } else {
      printer.event_reporter(warning_codes::unknown_authorization);
      }*/

    //} else {
    //std::cout << "No tiene data" << std::endl;
    //}
}

// Función miembro: restart_manager(). 
// Invocada a través del comando -restart. 
// Ex. emi -restart 
void Manager::restart_manager() {
    Communicator printer;
    // Solicitamos la autorización del usuario para ejecutar el comando -restart
    printer.authorization_reporter(restart_command);
    // Capturamos la autorización
    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder(base);
        // Removemos el repositorio emi incluyendo todos sus archivos internos (action_mode::recursive)
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        // Construimos el repositorio emi con su configuración básica
        builder.repository_builder(current_path);
        printer.event_reporter(success_codes::emi_repository_restarted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, restart_command);
    } else {
        printer.event_reporter(warning_codes::unknown_authorization);
    }
}

// Función miembro: bye_manager(). 
// Invocada a través del comando -bye. 
// Ex. emi -bye 
void Manager::bye_manager() {
    Communicator printer;
    // Solicitamos la autorización del usuario para ejecutar el comando -bye
    printer.authorization_reporter(bye_command);
    // Capturamos la autorización
    string authorization;
    std::cin >> authorization;
    if (authorization == confirmed_auth) {
        Builder builder;
        // Removemos el repositorio emi incluyendo todos sus archivos internos (action_mode::recursive)
        builder.repository_remover(base.emi_default_path, action_mode::recursive);
        printer.event_reporter(success_codes::emi_repository_deleted);
    } else if (authorization == denied_auth) {
        printer.event_reporter(notification_codes::cancelled_action, bye_command);
    } else {
        printer.event_reporter(warning_codes::unknown_authorization);
    }
}

Manager::~Manager() {}
