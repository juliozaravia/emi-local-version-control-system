/*
 * Project: EMI Control Version System 
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
    // Declaramos las variables iniciales que serán cargadas con data mediante las funciones de formateo y validación.
    // Nota: Utilizamos la librería filesystem para capturar la ruta actual y la transformamos a cadena.
    std::string current_path = fs::current_path().string();
    std::vector<std::string> arg_container;
    int validation_result = 0;

    // Creamos (inicializamos) el objeto "starter" para ejecutar las operaciones antes mencionadas.
    // Alimentamos las funciones con las variables necesarias.
    Starter starter(current_path, argc, argv);
    starter.input_formatter(arg_container);

    // Creamos (inicializamos) el objeto "printer" para mostrar en pantalla los mensajes de éxito o error según sea el caso
    // Para los casos específicos del comando "--help" y el comando "--version" no se realizará validación del repositorio emi
    // Debido a que estos comandos son informativos y están disponibles sin necesidad de crear un repositorio
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
            printer.event_reporter(warning_codes::wrong_amount_of_commands);
            return 0;
        }
    }

    // Comprobamos que el comando haya sido ejecutado desde una ruta válida
    starter.startup_validator(validation_result);
    // Creamos (inicializamos) el objeto "manager" que controlará las actividades desencadenadas por el comando
    Manager manager(current_path, arg_container);
    // Verificamos, según el comando ingresado, que nos encontremos en una ruta válida 
    // Adicionalmente validamos que el comando haya sido escrito correctamente y con la cantidad requerida de argumentos
    // Cada una de las eventualidades / problemas / errores encontrados al aplicar el comando ingresado será capturado por un bloque try / catch
    // Este bloque imprimirá el error respectivo para lectura del usuario
    if (validation_result == validation_codes::emi_and_path_valid) {
        if (arg_container.size() == 2) {
            if (command == start_command) {
                printer.event_reporter(warning_codes::emi_repository_exists);
            } else if (command == look_command) {
                try {
                    manager.look_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, look_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, look_command, err.what());
                }
            } else if (command == log_command) {
                try {
                    manager.log_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, log_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, log_command, err.what());
                }
            } else if (command == restart_command) {
                try {
                    manager.restart_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::emi_directories_not_created, restart_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(error_codes::emi_files_not_created, restart_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, restart_command, err.what());
                }
            } else if (command == bye_command) {
                try {
                    manager.bye_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::emi_directories_not_created, bye_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, bye_command, err.what());
                }
            } else {
                printer.event_reporter(warning_codes::unknown_command);
            }
        } else if (arg_container.size() == 3) {
            if (command == catch_command) {
                try {
                    manager.catch_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::unsuccessful_file_manipulation, catch_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, catch_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, catch_command, err.what());
                }
            } else if (command == ignore_command) {
                try {
                    manager.ignore_manager();
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, ignore_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, ignore_command, err.what());
                }
            } else if (command == snapshot_command) {
                try {
                    manager.snapshot_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::unsuccessful_file_manipulation, snapshot_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, snapshot_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, snapshot_command, err.what());
                }
            } else if (command == drop_command) {
                try {
                    manager.drop_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::unsuccessful_file_manipulation, drop_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, drop_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, drop_command, err.what());
                }
            } else if (command == get_command) {
                try {
                    manager.get_manager();
                } catch (const fs::filesystem_error& err) {
                    printer.event_reporter(error_codes::unsuccessful_file_manipulation, get_command, err.what());
                } catch (const std::ios_base::failure& err) {
                    printer.event_reporter(warning_codes::file_not_open, get_command, err.what());
                } catch (const std::exception& err) {
                    printer.event_reporter(error_codes::emi_unknown_error, get_command, err.what());
                }
            } else {
                printer.event_reporter(warning_codes::unknown_command);
            }
        } else {
            printer.event_reporter(warning_codes::wrong_amount_of_commands);
        }
    } else if (validation_result == validation_codes::emi_and_path_not_valid) {
        if (arg_container.size() == 2) {
            if (command == start_command) {
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
        printer.event_reporter(warning_codes::parent_emi_repository_exists);
    }



    /*if (validation_result == validation_codes::emi_and_path_valid) {
      if (arg_container.size() == 2) {
      if (command == help_command) {
      printer.command_reporter();
      } else if (command == version_command) {
      printer.version_reporter();
      } else if (command == start_command) {
      printer.event_reporter(warning_codes::emi_repository_exists);
      } else if (command == look_command) {
      try {
      manager.look_manager();
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(warning_codes::file_not_open, look_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, look_command, err.what());
      }
      } else if (command == log_command) {
      try {
      manager.log_manager();
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(warning_codes::file_not_open, log_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, log_command, err.what());
      }
      } else if (command == restart_command) {
      try {
      manager.restart_manager();
      } catch (const fs::filesystem_error& err) {
      printer.event_reporter(error_codes::emi_directories_not_created, restart_command, err.what());
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(error_codes::emi_files_not_created, restart_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, restart_command, err.what());
      }
      } else if (command == bye_command) {
      try {
      manager.bye_manager();
      } catch (const fs::filesystem_error& err) {
      printer.event_reporter(error_codes::emi_directories_not_created, bye_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, bye_command, err.what());
      }
      } else {
      printer.event_reporter(warning_codes::unknown_command);
      }
      } else if (arg_container.size() == 3) {
      if (command == catch_command) {
      try {
      manager.catch_manager();
      } catch (const fs::filesystem_error& err) {
      printer.event_reporter(error_codes::unsuccessful_file_manipulation, catch_command, err.what());
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(warning_codes::file_not_open, catch_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, catch_command, err.what());
      }
      } else if (command == ignore_command) {
      try {
      manager.ignore_manager();
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(warning_codes::file_not_open, ignore_command, err.what());
      } catch (const std::exception& err) {
      printer.event_reporter(error_codes::emi_unknown_error, ignore_command, err.what());
      }
      } else if (command == snapshot_command) {
      try {
      manager.snapshot_manager();
      } catch (const fs::filesystem_error& err) {
      printer.event_reporter(error_codes::unsuccessful_file_manipulation, snapshot_command, err.what());
      } catch (const std::ios_base::failure& err) {
      printer.event_reporter(warning_codes::file_not_open, snapshot_command, err.what());
} catch (const std::exception& err) {
    printer.event_reporter(error_codes::emi_unknown_error, snapshot_command, err.what());
}
} else if (command == drop_command) {
    try {
        manager.drop_manager();
    } catch (const fs::filesystem_error& err) {
        printer.event_reporter(error_codes::unsuccessful_file_manipulation, drop_command, err.what());
    } catch (const std::ios_base::failure& err) {
        printer.event_reporter(warning_codes::file_not_open, drop_command, err.what());
    } catch (const std::exception& err) {
        printer.event_reporter(error_codes::emi_unknown_error, drop_command, err.what());
    }
} else if (command == get_command) {
    try {
        manager.get_manager();
    } catch (const fs::filesystem_error& err) {
        printer.event_reporter(error_codes::unsuccessful_file_manipulation, get_command, err.what());
    } catch (const std::ios_base::failure& err) {
        printer.event_reporter(warning_codes::file_not_open, get_command, err.what());
    } catch (const std::exception& err) {
        printer.event_reporter(error_codes::emi_unknown_error, get_command, err.what());
    }
} else {
    printer.event_reporter(warning_codes::unknown_command);
}
} else {
    printer.event_reporter(warning_codes::wrong_amount_of_commands);
}
} else if (validation_result == validation_codes::emi_and_path_not_valid) {
    if (arg_container.size() == 2) {
        if (command == help_command) {
            printer.command_reporter();
        } else if (command == version_command) {
            printer.version_reporter();
        } else if (command == start_command) {
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
        if (command == help_command) {
            printer.command_reporter();
        } else if (command == version_command) {
            printer.version_reporter();
        } else {
            printer.event_reporter(warning_codes::parent_emi_repository_exists);
        }
    } else {
        printer.event_reporter(warning_codes::parent_emi_repository_exists);
    }
}*/

return 0;
}

