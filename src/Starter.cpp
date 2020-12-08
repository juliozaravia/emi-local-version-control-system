#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "../include/Starter.h"
#include "../include/Helper.h"
#include "../include/Global.h"
#include "../include/Codes.h"

using std::string;
using std::vector;

namespace fs = std::filesystem;

// Constructor simple de tres argumentos
Starter::Starter(string current_path, int argument_count, char* argument_values[])
    : current_path{current_path},
    argument_count{argument_count},
    argument_values{argument_values} {
    }

// Contruimos un método que permita mover el contenido a un contenedor más "amigable" como vector<string>.
void Starter::input_formatter(vector<string>& arg_container) {
    std::copy(argument_values, argument_values + argument_count, std::back_inserter(arg_container));
}

// Construimos un método que nos informa si el repositorio emi es válido y si la ruta actual 
// desde donde se están solicitando las acciones es una ruta válida
void Starter::startup_validator(int& validation_result) {
    // Construimos manualmente las rutas necesarias
    // Nota: Una vez que el control haya pasado a la clase Manager las rutas serán construidas de manera automática
    string emi_default_path = current_path + "/" + emi_path;
    string config_main_file = emi_default_path + "/" + config_path + "/" + config_main;

    // Verificamos que la carpeta contenedora de los archivos de emi exista dentro de la ruta actual
    // Adicionalmente se valida también que el archivo de configuración exista
    // Ambas condicionales debe ser válidas para que el programa no se detenga e informe de la inconsistencia
    if (fs::exists(emi_default_path) && fs::exists(config_main_file)) {
        validation_result = validation_codes::emi_and_path_valid;
    } else {
        // Extraemos los "items" o nombres de carpeta dentro de la variable "current_path"
        // Eso quiere decir que si tenemos la ruta /usr/test/first-test/ 
        // El valor de los items luego de haber sido procesados será: usr, test, first-test
        Helper helper;
        vector<string> extracted_items;
        helper.items_extractor(extracted_items, current_path, '/');

        // Iteramos sobre los items extraídos y los utilizamos para armar rutas incrementales
        // Esto quiere decir que si tenemos los items: usr, test, first-test y empezamos a "armarlos"
        // tendremos los siguientes valores: /usr/, /usr/test/, /usr/test/fisrt-test
        string temporal_path;
        vector<string> incremental_paths;
        for(size_t iterA = 1; iterA < extracted_items.size(); iterA++) {
            temporal_path += "/" + extracted_items[iterA];
            if (iterA > 0) { incremental_paths.push_back(temporal_path); }
        }

        // Ordenamos las rutas construídas de acuerdo a su longitud 
        std::sort(incremental_paths.begin(), incremental_paths.end(), [](const string& first, const string& second) { 
                return first.size() > second.size(); });

        bool contains_emi_path = false;
        for (const string& evaluation_path : incremental_paths) {
            // Iteramos sobre cada ruta almacenada en *incremental_paths*. 
            for (const auto& file_or_folder : fs::directory_iterator(evaluation_path)) {
                // Debemos recordar que algunas rutas construidas contendrán un archivo
                if(fs::is_directory(file_or_folder)) {
                    string folder = file_or_folder.path().string();
                    // Validamos que la ruta evaluada contenga la ruta del *emi_path*
                    // De esta manera nos aseguramos que la solicitud (el comando) se ha ejecutado desde una sub-carpeta dentro de un proyecto rastreado
                    // Es decir, el repositorio emi existe en un nivel superior y la llamada se está haciendo desde un nivel inferior
                    if (folder.find(emi_path) != string::npos) {
                        contains_emi_path = true;
                        break;
                    }
                }
            }
            if (contains_emi_path) { break; }
        }
        
        if (!contains_emi_path) {
            validation_result = validation_codes::emi_and_path_not_valid;
        } else {
            validation_result = validation_codes::emi_valid_path_not_valid;
        }
    }
}

Starter::~Starter() {}

