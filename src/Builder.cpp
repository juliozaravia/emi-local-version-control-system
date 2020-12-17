/*
 * Project: EMI Personal Control Version System 
 * File: Builder Class - Implementation file
 * Description: Clase de ejecución. Nos permite realizar las acciones principales como
 * creación, registro, eliminado y transporte de directorios y/o archivos entre otras acciones
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <type_traits>
#include <algorithm>

#include "../include/Builder.h"
#include "../include/Helper.h"
#include "../include/Communicator.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::endl;
using std::vector;
using std::unordered_map;
using std::ofstream;
using std::stringstream;

namespace fs = std::filesystem;

Builder::Builder() {
}
Builder::Builder(Base base)
    : base{base} {
    }

/*
 * Builders
 */

// Descripción: Nos permite construir el repositorio que contendrá las versiones capturadas o guardadas de los archivos...
// ..., las bases de datos de versiones de archivos y los archivos de configuración en general 
void Builder::repository_builder(const string& current_path) {
    // Creamos la estructura de directorios
    fs::create_directory(base.emi_default_path);
    fs::create_directory(base.db_default_path);
    fs::create_directory(base.version_default_path);
    fs::create_directory(base.config_default_path);
    fs::create_directory(base.version_catch_path);
    fs::create_directory(base.version_main_path);
    fs::create_directory(base.version_temp_path);
    // Creamos los archivos de bases de datos
    ofstream db_catch_ostrm(base.db_catch_file, std::ios::out | std::ios::binary);
    db_catch_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_catch_ostrm.close();
    ofstream db_main_ostrm(base.db_main_file, std::ios::out | std::ios::binary);
    db_main_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_main_ostrm.close();
    ofstream db_temp_ostrm(base.db_temp_file, std::ios::out | std::ios::binary);
    db_temp_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    db_temp_ostrm.close();
    // Creamos los archivos de configuración
    ofstream config_main_ostrm(base.config_main_file, std::ios::out | std::ios::binary);
    config_main_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    config_main_ostrm << std::hash<string> {}(base.emi_default_path) << endl;
    config_main_ostrm << current_path << endl;
    config_main_ostrm.close();
    ofstream config_ignore_ostrm(base.config_ignore_file, std::ios::out | std::ios::binary);
    config_ignore_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    config_ignore_ostrm << current_path + "/" + emi_path << endl;
    config_ignore_ostrm.close();
}

// Descripción: Nos permite crear directorios
// Según el tipo de contenedor recibido se podrán crear directorios de manera individual o de manera grupal
template <typename T>
void Builder::directory_builder(const T& directory_container) {
    if constexpr (std::is_same_v<T,string>) {
        fs::create_directory(directory_container);
    } else if constexpr (std::is_same_v<T,unordered_map<string,bool>>) {
        for (const auto& directory : directory_container) {
            if (!directory.second) {
                fs::create_directories(directory.first);
            }
        }
    }
}
template void Builder::directory_builder<string>(const string&);
template void Builder::directory_builder<unordered_map<string,bool>>(const unordered_map<string,bool>&);

/*
 * Cleaners
 */

// Descripción: Nos permite limpiar la data registrada en un archivo
void Builder::data_cleaner(const string& target_file) {
    // Abrimos el stream asociado al archivo respectivo.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::trunc);
    // Establecemos la máscara de excepción de la secuencia.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // Cerramos y limpiamos el stream
    target_file_ostrm.close();
    target_file_ostrm.clear();
}

/*
 * Catchers & Savers
 */

// Descripción: Nos permite capturar la versión (datos que componen el estado y contenido) de un archivo individual o grupo de archivos
template <typename T>
void Builder::data_catcher(const T& data_container, const string& target_file) {
    // Abrimos el stream asociado al archivo respectivo.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // Establecemos la máscara de excepción de la secuencia.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // Según el tipo de contenedor se capturará una o varias versiones de archivos
    // Se registra en la base de datos de versiones de archivos capturados...
    // ... cada uno de los datos que componen la estructura de la versión de un archivo
    if constexpr (std::is_same_v<T,File>) {
        target_file_ostrm << data_container.file << ","
            << data_container.file_hash << ","
            << data_container.file_path << ","
            << data_container.file_path_hash << ","
            << data_container.version << ","
            << data_container.version_name << ","
            << data_container.file_name << ","
            << data_container.file_extension << ","
            << data_container.catch_date << ","
            << data_container.snap_hash << ","
            << data_container.snap_version << ","
            << data_container.snap_date << ","
            << data_container.comment
            << endl;
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (auto data : data_container) {
            target_file_ostrm << data.file << ","
                << data.file_hash << ","
                << data.file_path << ","
                << data.file_path_hash << ","
                << data.version << ","
                << data.version_name << ","
                << data.file_name << ","
                << data.file_extension << ","
                << data.catch_date << ","
                << data.snap_hash << ","
                << data.snap_version << ","
                << data.snap_date << ","
                << data.comment
                << endl;
        }
    }
    // Cerramos y limpiamos el stream
    target_file_ostrm.close();
    target_file_ostrm.clear();
}
template void Builder::data_catcher<File>(const File&, const string&);
template void Builder::data_catcher<vector<File>>(const vector<File>&, const string&);

// Descripción: Nos permite guardar la versión (datos que componen el estado y contenido) de un archivo individual o grupo de archivos
void Builder::data_saver(const vector<string>& rows, const string& target_file, const string& timepoint, const string& timepoint_hash, const string& comment) {
    // Abrimos el stream asociado al archivo respectivo.
    ofstream db_main_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // Establecemos la máscara de excepción de la secuencia.
    db_main_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // Recorremos cada una de las filas extraídas de la base de datos de versiones de archivos capturados 
    for (const auto& row : rows) {
        string version_name;
        // Pasamos la fila extraída a un stringstream
        stringstream row_strm(row);

        unsigned int temp_counter = 0;
        while (std::getline(row_strm, version_name, ',')) {
            // Cuando lleguemos al item correspondiente al nombre de la version (nombre físico del archivo guardado como versión) rompemos el bucle
            // De esta manera la variable temporal version_name contendrá el nombre de la versión que necesitamos
            if (temp_counter == db_pos::version_name) { break; }
            temp_counter++;
        }
        // 'Recortamos' la fila extraída de tal manera que guardamos los datos almacenados en la fase de captura de versión
        // Solo serán excluidos de la fila los valores vacíos que serán llenados más adelante
        string trimmed_row = row.substr(0, row.size() - 17);
        // Construimos la ruta donde será guardada la versión del archivo
        // Nótese que todos los archivos irán registrados en una carpeta. De esta manera nos aseguramos que físicamente también estén agrupados
        string main_version_name = base.version_main_path + "/" + timepoint_hash + "/" + version_name; 
        // Registramos en la base de datos de versiones de archivos guardados los datos necesarios
        // Nótese que se está registrando también la variable 'trimmed_row' que anteriormente fue extraída
        db_main_file_ostrm << trimmed_row << ","
            << timepoint_hash << ","
            << main_version_name << ","
            << timepoint << ","
            << comment << endl;
    }
    // Cerramos y limpiamos el stream
    db_main_file_ostrm.close();
    db_main_file_ostrm.clear();
}

/*
 * Inserters
 */

// Descripción: Nos permite insertar en un archivo (generalmente una base de datos de versiones) uno o varios registros
template <typename T>
void Builder::data_inserter(const T& row_or_rows, const string& target_file) {
    // Abrimos el stream asociado al archivo respectivo.
    ofstream target_file_ostrm(target_file, std::ios::out | std::ios::binary | std::ios::app);
    // Establecemos la máscara de excepción de la secuencia.
    target_file_ostrm.exceptions(ofstream::failbit | ofstream::badbit);
    // Según el tipo de contenedor recibido insertamos uno o varios registros
    if constexpr (std::is_same_v<T,string>) {
        target_file_ostrm << row_or_rows << endl;
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& row : row_or_rows) {
            target_file_ostrm << row << endl;
        }
    }
    // Cerramos y limpiamos el stream
    target_file_ostrm.close();
    target_file_ostrm.clear();
}
template void Builder::data_inserter<string>(const string&, const string&);
template void Builder::data_inserter<vector<string>>(const vector<string>&, const string&);

/*
 * Removers
 */

// Descripción: Nos permite eliminar un directorio o directorios 
void Builder::repository_remover(const string& target_folder, int mode) {
    // Según el modo recibido podemos eliminar un directorio de manera estándar...
    // ... o, podemos eliminar el directorio de manera recursiva (es decir, eliminar el directorio y su contenido recursivamente)
    if (mode == action_mode::simple) {
        fs::remove(target_folder);
    } else if (mode == action_mode::recursive) {
        fs::remove_all(target_folder);
    }
}

// Descripción: Nos permite remover un archivo individual o grupo de archivos 
template <typename T>
void Builder::file_remover(const T& file_container, int data_identifier) {
    // Segun el tipo de contenedor recibido eliminamos uno o varios archivos
    if constexpr (std::is_same_v<T,string>) {
        fs::remove(file_container);
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        for (auto& item : file_container) {
            fs::remove(item);
        }
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        string file_to_remove;
        for (auto& data : file_container) {
            // En este caso, la asignación de un 'data_identifier' nos indica si debemos eliminar...
            // ... un archivo original o una versión almacenada
            if (data_identifier == db_pos::file) {
                file_to_remove = data.file;    
            } else if (data_identifier == db_pos::version) {
                file_to_remove = data.version;
            }
            fs::remove(file_to_remove);
        }
    } else if constexpr (std::is_same_v<T,unordered_map<string,bool>>) {
        for (auto& file : file_container) {
            if (file.second) {
                fs::remove(file.first);
            } 
        }
    }
}
template void Builder::file_remover<string>(const string&, int);
template void Builder::file_remover<vector<string>>(const vector<string>&, int);
template void Builder::file_remover<vector<File>>(const vector<File>&, int);
template void Builder::file_remover<unordered_map<string,bool>>(const unordered_map<string,bool>&, int);

/*
 * Transportes
 */

// Descripción: Nos permite mover copias de archivos de un directorio a otro
template<typename T>
void Builder::file_transporter(const T& data_container, const string& target_folder, const string& target_sub_folder) {
    string original_file;
    string temporal_file;
    // Según el tipo de contenedor podemos copiar un archivo individual o múltiples archivos
    if constexpr (std::is_same_v<T,File>) {
        original_file = data_container.file;
        // Construimos la ruta a donde enviaremos la copia del archivo
        temporal_file = target_folder + "/" + data_container.version_name;
        // Copiamos el archivo desde su ruta original a su ruta final
        fs::copy_file(original_file, temporal_file);
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        for (const auto& data : data_container) {
            original_file = data.file;
            // Construimos la ruta a donde enviaremos la copia del archivo
            temporal_file = target_folder + "/" + data.version_name;
            // Copiamos el archivo desde su ruta original a su ruta final
            fs::copy_file(original_file, temporal_file);
        }
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        // Se define la ruta del subdirectorio dentro del directorio de destino
        // Este caso especial se aplica cuando la variable 'target:sub_folder' tiene contenido asignado
        string temporal_path = target_folder + "/" + target_sub_folder; 
        // Se crea el subdirectorio
        fs::create_directory(temporal_path);

        for (const auto& original_file : data_container) {
            string version_name = fs::path(original_file).filename().string();
            temporal_file = temporal_path + "/" + version_name;
            // Copiamos el archivo desde su ruta original a su ruta final
            fs::copy_file(original_file, temporal_file);
        }  
    }
}
template void Builder::file_transporter<File>(const File&, const string&, const string&);
template void Builder::file_transporter<vector<File>>(const vector<File>&, const string&, const string&);
template void Builder::file_transporter<vector<string>>(const vector<string>&, const string&, const string&);

// Descripción: Nos permite mover copias de archivos de un directorio a otro
// Este método ha sido construido para el caso específico requerido en el método 'Manager -> get_manager()'
void Builder::special_transporter(const vector<string>& original_files, const vector<string>& final_files) {
    for (unsigned int i = 0; i < original_files.size(); i++) {
        fs::copy_file(original_files.at(i), final_files.at(i));
    }
}

/*
 * Others
 */

// Descripción: Nos permite cambiar el nombre (renombrar) de un archivo o directorio 
void Builder::file_renamer(const string& selected_name, const string& target_folder, const string& target_sub_folder) {
    string temporal_path_name = target_folder + "/" + target_sub_folder;
    string final_path_name = target_folder + "/" + selected_name;
    fs::rename(temporal_path_name, final_path_name);
}

Builder::~Builder() {}
