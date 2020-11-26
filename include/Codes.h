#ifndef CODES_H
#define CODES_H

enum success_codes {
    emi_repository_created = 100,
    version_catched,
    version_saved,
    argument_file_updated,
    file_ignored,
    emi_repository_restarted,
    emi_repository_deleted,
    version_dropped
};

enum warning_codes {
    emi_repository_exists = 200,
    parent_emi_repository_exists,
    emi_repository_not_exists,
    unknown_command,
    wrong_amount_of_commands,
    identical_version_in_standby,
    identical_version_saved,
    file_not_open,
    no_files_to_save,
    file_not_found,
    file_already_ignored,
    unknown_authorization,
    file_not_catched, 
    file_in_use
};

enum error_codes {
    emi_directories_not_created = 300,
    emi_files_not_created,
    unsuccessful_file_manipulation,
    inconsistency_detected,
    emi_unknown_error
};

enum validation_codes {
    emi_and_path_valid = 400,
    emi_and_path_not_valid,
    emi_valid_path_not_valid
};

enum notification_codes {
    cancelled_action = 500,
    no_files_found
};

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

