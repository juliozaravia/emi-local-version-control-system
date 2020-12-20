/*
 * Project: Emi Local Version Control System 
 * File: Codes file 
 * Description: Support header file. It allows us to have all the necessary codes 
 * available to execute the operations requested by the user.
 * @author
 * Julio Zaravia <hey@juliozaravia.com>
 */

#ifndef CODES_H
#define CODES_H

// List of codes for operations that complete successfully.
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

// List of codes for operations truncated by some unexpected event that can be recovered.
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

// List of codes for operations truncated by some unforeseen event that cannot be recovered.
enum error_codes {
    unable_to_manipulate_files_or_directories = 300,
    unable_to_open_files,
    inconsistency_detected,
    emi_unknown_error
};

// List of codes that indicates the status of the emi repository when a command is executed.
enum validation_codes {
    emi_and_path_valid = 400,
    emi_and_path_not_valid,
    emi_valid_path_not_valid
};

enum notification_codes {
    cancelled_action = 500,
    no_files_found
};

// List of codes that represent the position of a certain value within the database of captured or saved versions.
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

// List of codes used to modify the activities (or behavior) in a method as necessary.
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

