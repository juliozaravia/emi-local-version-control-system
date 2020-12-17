/*
 * Project: EMI Personal Control Version System 
 * File: Helper Class - Implementation file
 * Description: Clase de apoyo de operaciones. Nos permite realizar las acciones complementarias y de soporte
 * a las acciones principales como creación, registro, eliminado y transporte de directorios y/o archivos entre otras acciones
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <type_traits>

#include "../include/Helper.h"
#include "../include/Structures.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::vector;
using std::stringstream;
using std::ifstream;
using std::unordered_map;
using std::unordered_multimap;

namespace fs = std::filesystem;

Helper::Helper() {}

/*
 * Comparators
 */

// Descripcion: Nos permite comparar 2 cadenas de texto retornando el valor de verdadero o falso según corresponda 
bool Helper::hash_comparator(const string& temporal_file_hash, const unsigned int& data_file_hash) {
    bool is_same_hash = false;
    if (std::to_string(data_file_hash) == temporal_file_hash) {
        is_same_hash = true;
    }
    return is_same_hash;
}

/*
 * Extractors
 */

// Descripcion: Nos permite extraer data de un archivo y almacenarla en un contenedor según los parámetros complementarios 
void Helper::rows_extractor(vector<string>& rows, const string& target_file, const string& comparison_row, int mode, int item_position) {
    // Abrimos el stream asociado al archivo respectivo.
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    // Establecemos la máscara de excepción de la secuencia.
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);
    // Se bifurca en base a los parámetros complementarios
    try {
        string target_file_row;
        if (comparison_row.empty()) {
            // Extraemos línea por línea toda la data del archivo y la almacenamos en un contenedor
            while (std::getline(target_file_istrm, target_file_row)) {
                rows.push_back(target_file_row);
            }
        } else {
            if (mode == action_mode::different_to_row) {
                // Extraemos línea por línea toda la data del archivo obviando la línea correspondiente a la cadena de comparación
                while (std::getline(target_file_istrm, target_file_row)) {
                    if (target_file_row != comparison_row) {
                        rows.push_back(target_file_row);
                    }
                }
            } else if (mode == action_mode::similar_to_item) {
                // Extraemos línea por línea toda la data del archivo que coincida con la cadena de comparación
                while (std::getline(target_file_istrm, target_file_row)) {
                    vector<string> extracted_items;
                    items_extractor(extracted_items, target_file_row);
                    if (extracted_items.at(item_position) == comparison_row) {
                        rows.push_back(target_file_row);
                    }
                }
            }
        }
    } catch (const std::ios_base::failure& err) {
        if (!target_file_istrm.eof()) throw;
    }
    // Cerramos y limpiamos el stream
    target_file_istrm.close();
    target_file_istrm.clear();
}

// Descripción: Nos permite buscar y extraer la fila de data del archivo objetivo que coincida con el nombre del archivo enviado 
string Helper::row_extractor(const string& file, const string& target_file) {
    string extracted_row;
    vector<string> rows;
    // Utilizamos el metodo rows_extractor para llenar todas las filas del archivo objetivo en un contenedor
    rows_extractor(rows, target_file);

    for (const auto& row : rows) {
        // Extraemos el nombre del archivo de la fila extraída
        string trimmed_file = row.substr(0, file.size());
        // Comparamos el nombre del archivo recibido con el nombre del archivo extraído
        // Si coinciden se finaliza el ciclo y se retorna el valor encontrado
        if (file == trimmed_file) {
            extracted_row = row;
            break;
        }
    }
    return extracted_row;
}

// Descripción: Nos permite extraer los items de una cadena de texto
void Helper::items_extractor(vector<string>& items, const string& row, char separator) {
    string row_item;
    // Pasamos la cadena de texto recibida al stringstream
    stringstream row_strm(row);
    // Recorremos el strigstream y capturamos en una variable cada item
    // Almacenamos el valor extraído en un contenedor
    while (std::getline(row_strm, row_item, separator)) {
        items.push_back(row_item);
    }
}

// Descripción: Extraemos data específica de un archivo o contenedor 
template<typename T, typename U>
void Helper::content_extractor(T& item_or_items, const U& target_container, int item_position) {
    // El contenedor que recibirá la data es una cadena de texto
    // Esto significa que el valor a almacenar es individual
    if constexpr (std::is_same_v<T,string>) {
        vector<string> extracted_items;
        // Usamos el método items_extractor para extraer todos los items del archivo objetivo
        // Usamos el valor de posición recibido para extraer específicamente el valor del item en esa posición
        // Almacenamos el valor extraído en el contenedor
        items_extractor(extracted_items, target_container);
        item_or_items = extracted_items.at(item_position);
        // El contenedor que recibirá la data es un contendor múltiple (Vector)
        // Esto significa que se almacenarán varios valores en él
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        vector<string> rows;
        // El contenedor del cual extraeremos la data es un cadena de texto
        // Esto significa que esta cadena de texto hace referencia a un nombre de archivo
        if constexpr (std::is_same_v<U,string>) {
            // Extraemos todas las filas del archivo objetivo y lo almacenamos en un contenedor
            rows_extractor(rows, target_container);
            // El contenedor del cual extraeremos la data es un contenedor múltiple
            // Esto significa que las filas necesarias ya fueron extraídas previamente
        } else if constexpr (std::is_same_v<U,vector<string>>) {
            rows = target_container;    
        }

        for (const auto& row : rows) {
            vector<string> extracted_items;
            // Extraemos todos los items de cada una de las filas del contenedor
            // Usamos el valor de posición recibido para extraer específicamente el valor del item en esa posición
            // Almacenamos el valor extraído en el contenedor
            items_extractor(extracted_items, row);
            item_or_items.push_back(extracted_items.at(item_position));
        }
    }
}
template void Helper::content_extractor<string, string>(string&, const string&, int);
template void Helper::content_extractor<vector<string>,string>(vector<string>&, const string&, int);
template void Helper::content_extractor<vector<string>,vector<string>>(vector<string>&, const vector<string>&, int);

/*
 * Checkers
 */

// Descripción: Nos permite verificar si un archivo tiene contenido o no
bool Helper::content_checker(const string& target_file) {
    // Abrimos el stream asociado al archivo respectivo.
    ifstream target_file_istrm(target_file, std::ios::in | std::ios::binary);
    // Establecemos la máscara de excepción de la secuencia.
    target_file_istrm.exceptions(ifstream::failbit | ifstream::badbit);

    bool file_has_data = true;
    // Leemos la data del archivo y verificamos que tenga contenido
    if (target_file_istrm.peek() == ifstream::traits_type::eof()) { file_has_data = false; }
    // Cerramos y limpiamos el stream
    target_file_istrm.close();
    target_file_istrm.clear();
    // Devolvemos el resultado
    return file_has_data;
}

// Descripción: Nos permite verificar si un archivo o grupo de archivos existen o no y devolver su estado
template <typename T>
bool Helper::existence_checker(const T& file_or_files, unordered_map<string,bool>& status) { 
    bool exists = false;
    // El contenedor del archivo es una cadena de texto
    // Esto significa que es un archivo individual
    if constexpr (std::is_same_v<T,string>) {
        // Verificamos que el archivo exista
        if (fs::exists(file_or_files)) {
            exists = true;
        }
        // El contenedor del archivo es un contenedor múltiple
        // Esto significa que se debe verificar la existencia de varios archivos
    } else if constexpr (std::is_same_v<T,vector<string>>) {
        unsigned int temp_counter = 0;
        // Verificamos la existencia de cada archivo
        // Si el archivo existe se incrementa un contador 
        // Se inserta en el contenedor de estado el nombre del archivo y su estado asociado true si existe, false si no existe
        for (const auto& file : file_or_files) {
            if (fs::exists(file)) {
                temp_counter++;
                status.insert(make_pair(file,true));
            } else {
                status.insert(make_pair(file,false));
            }
        }

        // Si el contador es igual a la cantidad de items del contenedor se puede asegurar que todos los archivos existen
        if (temp_counter == file_or_files.size()) {
            exists = true;
        }
    }
    return exists;
}
template bool Helper::existence_checker<std::string>(const string&, unordered_map<string,bool>&);
template bool Helper::existence_checker<std::vector<std::string>>(const vector<string>&, unordered_map<string,bool>&);

// Descripción: Nos permite validar la existencia del archivo en la lista de archivos ignorados.
bool Helper::ignored_file_checker(const string& file, const string& target_file) {
    bool is_ignored = false;
    // Se utiliza el método rows_extractor para extraer las filas del archivo de ignorados
    // Debemos recordar que el archivo de ignorados no solo almacena archivos sino también rutas o directorios
    vector<string> ignored_rows;
    rows_extractor(ignored_rows, target_file);

    for (const auto& ignored_item : ignored_rows) {
        // Creamos un sub-string recortando el nombre del archivo por procesar
        // Este nuevo item debe ser un folder o directorio
        string ignored_folder = file.substr(0, ignored_item.size());
        // Validamos que tanto los archivos como los directorios no se encuentren en la lista de archivos ignorados
        if (file == ignored_item || ignored_folder == ignored_item) {
            is_ignored = true;
        }
    }
    return is_ignored;
}

/*
 * Generators
 */

// Nos permite contruir la ruta completa de un archivo en base a la ruta absoluta (ruta actual) y la ruta relativa del archivo (incluyendo el nombre del archivo) 
string Helper::location_generator(const string& file, const string& absolute_path) {
    string file_location = absolute_path + "/" + file;
    return file_location;
}

// Descripción: Nos permite generar un valor hash en base al contenido de un archivo o una cadena de texto simple
unsigned int Helper::hash_generator(const string& target_container, int mode) {
    unsigned int hash_value = 0;
    // La data necesita ser extraída previamente de un archivo (action_mode::recursive)
    if (mode == action_mode::recursive) {
        // Abrimos el stream asociado al archivo respectivo.
        ifstream target_container_istrm(target_container, std::ios::in | std::ios::binary);
        // Establecemos la máscara de excepción de la secuencia.
        target_container_istrm.exceptions(ifstream::failbit | ifstream::badbit);
        // Almacenamos la data extraida en un contenedor (buffer)
        string argumentfile_data_container {
            std::istreambuf_iterator<char>(target_container_istrm),
                std::istreambuf_iterator<char>()
        };
        // Cerramos y limiamos el stream
        target_container_istrm.close();
        target_container_istrm.clear();
        // Generamos el valor hash en base al contenido del archivo
        hash_value = std::hash<string> {}(argumentfile_data_container);
        // La data será generada en base a una cadena de texto
    } else if (mode == action_mode::simple) {
        // Generamos el valor hash en base a la cadena de texto 
        hash_value = std::hash<string> {}(target_container);
    }

    return hash_value;
}

// Descripción: Nos permite generar (capturar) un punto de tiempo exacto
void Helper::timepoint_generator(string& timepoint) {
    // Capturamos la hora del reloj interno
    auto current_timepoint = std::chrono::system_clock::now();
    // Le damos el formato de tiempo necesario para poder ejecutar las demás operaciones
    std::time_t formated_timepoint = std::chrono::system_clock::to_time_t(current_timepoint);
    char formated_timepoint_buffer[20];
    // Le damos el formato en el que el punto de tiempo será mostrado
    strftime(formated_timepoint_buffer, sizeof(formated_timepoint_buffer), "%H:%M:%S %d-%m-%Y", localtime(&formated_timepoint));
    timepoint = formated_timepoint_buffer;
}

/*
 * Organizers
 */

// Descripción: Nos permite llenar la estructura de datos de la versión del archivo que usarán los métodos de captura y guardado de versiones 
template<typename T, typename U>
void Helper::data_organizer(T& data_container, const U& rows, const string& target_folder, int mode) {
    // Capturamos la fecha y hora en la que se hizo la llamada al comando necesario para la captura o guardado de la(s) versión(es)
    string temporal_date;
    timepoint_generator(temporal_date);

    // El contenedor 'data_container' donde registraremos la data es una estructura individual
    if constexpr (std::is_same_v<T,File>) {
        // El contenedor 'rows' que trae la data que deberemos procesar para llenar la estructura, es una cadena de texto
        // Esto significa que es simplemente la ruta del archivo a procesar
        data_container.file = rows;
        // Extraemos del nombre del archivo o generamos la data requerida por la estructura.
        // La data requerida es: Ruta completa del archivo, valor hash del archivo, nombre del archivo, extensión del archivo...
        // ... Ruta del archivo sin considerar su nombre, valor hash generado con la ruta previa, nombre de la versión del archivo...
        // ... Ruta completa de la versión del archivo, fecha y hora capturadas al momento de ejecutar el método
        data_container.file_hash = hash_generator(data_container.file, action_mode::recursive);
        data_container.file_name = fs::path(data_container.file).filename().string();
        data_container.file_extension = fs::path(data_container.file).extension().string();
        data_container.file_path = fs::path(data_container.file).parent_path().string();
        data_container.file_path_hash = hash_generator(data_container.file_path, action_mode::simple);
        data_container.version_name = std::to_string(data_container.file_path_hash) + "-" + std::to_string(data_container.file_hash) + "-" + data_container.file_name;
        data_container.version = target_folder + "/" + data_container.version_name;
        data_container.catch_date = temporal_date;
        // El contenedor 'data_container' donde registraremos la data es una contenedor múltiple
    } else if constexpr (std::is_same_v<T,vector<File>>) {
        // El contenedor 'rows' que trae la data que deberemos procesar para llenar la estructura, es una contenedor múltiple
        // Esto significa que debemos recorrer su contenido y procesarlo antes de llenar las estructuras
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
            // Extraemos la información de cada una de las filas extraídas
            // Llenamos con esta data las valores correspondientes
            // Existen valores pendientes que serán llenados según el modo impuesto por el desarrollador
            File data;
            data.file = items.at(db_pos::file);
            data.file_name = items.at(db_pos::file_name);
            data.file_extension = items.at(db_pos::file_extension);
            data.file_path = items.at(db_pos::path_name);
            data.file_path_hash = std::stoul(items.at(db_pos::path_hash));
            // Según el modo indicado podemos extraer la data del contenedor 'rows' o generarla
            // Extraer la data indica que el archivo no ha sido modificado y su data registrada es la más reciente
            if (mode == action_mode::built) {
                data.file_hash = std::stoul(items.at(db_pos::file_hash));
                data.version_name = items.at(db_pos::version_name);
                data.version = items.at(db_pos::version);
                data.catch_date = items.at(db_pos::catch_date);
                // Generar la data indica que el archivo ha sido modificado y necesitamos generar data actualizada
            } else if (mode == action_mode::to_build) {
                data.file_hash = hash_generator(data.file, action_mode::recursive);
                data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name;
                data.version = target_folder + "/" + data.version_name;
                data.catch_date = temporal_date;
            }
            data_container.push_back(data);
        }
    }
}
template void Helper::data_organizer<File,string>(File&, const string&, const string&, int);
template void Helper::data_organizer<vector<File>,vector<string>>(vector<File>&, const vector<string>&, const string&, int);

// Descripción: Nos permite llenar la estructura de datos de la versión del archivo que usarán los métodos de captura y guardado de versiones 
template<typename T> 
void Helper::data_organizer(vector<File>& data_container, const T& files, const string& target_folder) {
    // Capturamos la fecha y hora en la que se hizo la llamada al comando necesario para la captura o guardado de la(s) versión(es)
    string temporal_date;
    timepoint_generator(temporal_date);

    for (const auto& file : files) {
        File data;
        // El contenedor 'files' que trae los nombres de los archivos a procesar es del tipo unordered_map.
        // Esto significa que deberemos tomar el segundo valor de esta estructura para asignarla como nombre del archivo
        if constexpr (std::is_same_v<T,unordered_map<string,string>>) {
            data.file = file.second;
            // El contenedor 'files' que trae los nombres de los archivos a procesar es del tipo vector.
            // Esto significa que podemos asignar directamente el valor de cada item como nombre del archivo
        } else if constexpr (std::is_same_v<T,vector<string>>) {
            data.file = file;
        }
        data.file_hash = hash_generator(data.file, action_mode::recursive);
        data.file_name = fs::path(data.file).filename().string();
        data.file_extension = fs::path(data.file).extension().string();
        data.file_path = fs::path(data.file).parent_path().string();
        data.file_path_hash = hash_generator(data.file_path, action_mode::simple);
        data.version_name = std::to_string(data.file_path_hash) + "-" + std::to_string(data.file_hash) + "-" + data.file_name;
        data.version = target_folder + "/" + data.version_name;
        data.catch_date = temporal_date;

        data_container.push_back(data);
    }
}
template void Helper::data_organizer<std::unordered_map<std::string,std::string>>(vector<File>&, const unordered_map<string,string>&, const string&);
template void Helper::data_organizer<std::vector<std::string>>(vector<File>&, const vector<string>&, const string&);

// Descripción: Nos permite filtrar los archivos disponibles para ser procesados de los archivos que se encuentran registrados como ignorados  
void Helper::availability_organizer(unordered_map<string,string>& available_files, const vector<string>& rows, const string& current_path) {
    // Recorremos todos los archivos o carpetas a partir de la ruta actual
    for (const auto& file_or_folder : fs::recursive_directory_iterator(current_path)) {
        // Filtramos las carpetas, de tal manera, solo estaremos trabajando con archivos
        if (!fs::is_directory(file_or_folder)) {
            unsigned int temp_counter = 0;
            string formatted_file = file_or_folder.path().string();
            // Recorremos el contenedor 'rows' que contiene los archivos registrados como ignorados
            for (auto& ignored_file_or_folder : rows) {
                // Hacemos que el tamaño del 'formatted_file' coincida con el tamaño del archivo registrado como ignorado
                string comparison_file = formatted_file.substr(0, ignored_file_or_folder.size());
                // Comparamos ambos nombres de archivo
                // Si son diferentes aumentamos el valor de un contador temporal 
                if (ignored_file_or_folder != comparison_file) { 
                    temp_counter++; 
                } 
            }

            unsigned int temporal_hash = 0;
            // La cantidad almacenada en el contador es igual al número de items que tiene el contenedor 'rows'
            // Esto significa que el archivo que está siendo procesado no ha sido registrado en la lista de ignorados
            if (temp_counter == rows.size()) {
                temporal_hash = hash_generator(formatted_file, action_mode::recursive);
                // Insertamos en una estructura de tipo unordered_map el valor hash del contenido del archivo como clave...
                // y el nombre del archivo como valor asociado
                available_files.insert(make_pair(std::to_string(temporal_hash), formatted_file));
            }
        }
    }
}

// Descripción: Nos permite agrupar archivos según su estado: No rastreados, modificados, capturados o guardados 
void Helper::status_organizer(unordered_map<string,string>& untracked_files, unordered_map<string,string>& modified_files, unordered_map<string,string>& saved_files, const string& target_file) {
    string trimmed_target_file = target_file.substr(target_file.size() - db_catch.size(), db_catch.size());
    vector<string> rows;
    rows_extractor(rows, target_file);

    unordered_map<string,string> temporal_files;
    if (trimmed_target_file == db_catch) {
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
            temporal_files.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
        }
    } else {
        unordered_map<string,string> latest_version_checker;
        for (const auto& row : rows) {
            vector<string> items;
            items_extractor(items, row);
            for (auto latest_version_item : latest_version_checker) {
                if (items.at(db_pos::file) == latest_version_item.second) {
                    temporal_files.erase(latest_version_item.first);
                }
            }
            temporal_files.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
            latest_version_checker.insert(make_pair(items.at(db_pos::file_hash),items.at(db_pos::file)));
        }
    }

    unsigned int hash_match_counter = 0;
    unsigned int filename_match_counter = 0;
    for (const auto& untracked_item : untracked_files) {
        for (const auto& saved_item : temporal_files) {
            if (untracked_item.second == saved_item.second) {
                saved_files.insert(make_pair(saved_item.first,saved_item.second));
                if (untracked_item.first != saved_item.first) {
                    modified_files.insert(make_pair(untracked_item.first,untracked_item.second));
                    hash_match_counter++;
                }
                filename_match_counter++;
                break;
            }
        }
    }

    if (filename_match_counter > 0) {
        for (const auto& saved_file : saved_files) {
            untracked_files.erase(saved_file.first);
        }
    }

    if (hash_match_counter > 0) {
        for (const auto& modified_file : modified_files) {
            untracked_files.erase(modified_file.first);
        }
    }
}

// Descripción: Nos permite estructurar la información de cada una de las oportunidades en las que se aplicó el guardado de versiones de archivos
void Helper::log_organizer(Log& log, vector<Log>& log_info, unordered_multimap<string,string>& saved_files, const vector<string>& rows) {
    string temp_hash;
    string temp_date;
    string temp_comment;
    // Recorremos todas las filas extraídas de la base de datos de versiones de archivos guardados 
    for (const auto& row : rows) {
        // Extraemos los items de cada una de las filas y las almacenamos en un contenedor
        vector<string> items;
        items_extractor(items, row);
        // Insertamos en una estructura de tipo unordered_map el valor hash del snapshot como clave...
        // y el nombre del archivo como valor asociado
        saved_files.insert(make_pair(items.at(db_pos::snap_hash),items.at(db_pos::file)));
        // Extraemos del grupo de versiones de archivos los valores: valor hash del snapshot, fecha y hora del guardado de los archivos...
        // y, el comentario que escribe el usuario con respecto a la acción realizada o motivo del guardado de archivos
        if (temp_hash != items.at(db_pos::snap_hash)) {
            log.snapshot_code = items.at(db_pos::snap_hash);
            log.snapshot_date = items.at(db_pos::snap_date);
            log.snapshot_comment = items.at(db_pos::comment);
            log_info.push_back(log);
        }
        temp_hash = items.at(db_pos::snap_hash);
    }
}

// Descripción: Nos permite agrupar archivos según su estado: No rastreados, modificados, capturados o guardados 
void Helper::processed_files_organizer(vector<string>& saved_modified, vector<string>& saved_not_modified, const unordered_map<string,string>& modified_files, const unordered_map<string,string>& saved_files, const string& target_file) {
    for (auto saved_file : saved_files) {
        if (modified_files.empty()) {
            string temp_saved_not_modified = row_extractor(saved_file.second, target_file);
            saved_not_modified.push_back(temp_saved_not_modified);
        } else { 
            for (auto modified_file : modified_files) {
                if (saved_file.second == modified_file.second) {
                    string temp_saved_modified = row_extractor(saved_file.second, target_file);
                    saved_modified.push_back(temp_saved_modified);
                } else {
                    string temp_saved_not_modified = row_extractor(saved_file.second, target_file);
                    saved_not_modified.push_back(temp_saved_not_modified);
                }
            }
        }
    }

    std::sort(saved_not_modified.begin(), saved_not_modified.end());
    saved_not_modified.erase(std::unique(saved_not_modified.begin(), saved_not_modified.end()), saved_not_modified.end());

    for (auto item : saved_modified) {
        saved_not_modified.erase(std::remove(saved_not_modified.begin(), saved_not_modified.end(), item), saved_not_modified.end());
    }
}


void Helper::duplicate_organizer(vector<string>& items) {
    std::sort(items.begin(), items.end());
    items.erase(std::unique(items.begin(), items.end()), items.end());
}

Helper::~Helper() {}
