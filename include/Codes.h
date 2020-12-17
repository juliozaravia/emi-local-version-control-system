/*
 * Project: EMI Personal Control Version System 
 * File: Codes file 
 * Description: Archivo de apoyo. Nos permite tener disponibles todos los códigos
 * necesarios para ejecutar las operaciones solicitadas por el usuario
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#ifndef CODES_H
#define CODES_H

// Listado de códigos para operaciones que finalizan exitosamente
enum success_codes {
    emi_repository_created = 100,
    version_catched,
    version_saved,
    file_ignored,
    emi_repository_restarted,
    emi_repository_deleted,
    version_dropped,
    version_restored
};

// Listado de códigos para operaciones truncadas por algún evento imprevisto que se puede recuperar
enum warning_codes {
    emi_repository_exists = 200,
    parent_emi_repository_exists,
    emi_repository_not_exists,
    unknown_command,
    wrong_amount_of_commands,
    identical_version_in_standby,
    identical_version_saved,
    no_files_to_process,
    file_not_found,
    file_already_ignored,
    unknown_authorization,
    file_not_catched, 
    file_in_use,
    snapcode_not_found
};

// Listado de códigos para operaciones truncadas por algún evento imprevisto que no se puede recuperar
enum error_codes {
    unable_to_manipulate_files_or_directories = 300,
    unable_to_open_files,
    inconsistency_detected,
    emi_unknown_error
};

// Listado de códigos que indica el estado del repositorio emi cuando se ejecuta algún comando 
enum validation_codes {
    emi_and_path_valid = 400,
    emi_and_path_not_valid,
    emi_valid_path_not_valid
};

// Listado de códigos que simbolizan mensajes de tipo Notificación
enum notification_codes {
    cancelled_action = 500,
    no_files_found
};

// Listado de códigos que indica la posición de un determinado valor...
// ... dentro de la base de datos de versiones de archivos capturados o guardados
enum db_pos {
    file,
    file_hash,
    path_name,
    path_hash,
    version,
    version_name,
    file_name,
    file_extension,
    catch_date,
    snap_hash,
    snap_version,
    snap_date,
    comment
};

// Listado de códigos que sirven para modificar las actividades (o comportamiento) en un método según sea necesario
enum action_mode {
    built,
    to_build,
    simple,
    recursive,
    multiple,
    similar_to_row,
    different_to_row,
    similar_to_item,
    different_to_item
};

#endif // CODES_H

