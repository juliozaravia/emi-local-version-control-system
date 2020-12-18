/*
 * Project: EMI Personal Control Version System 
 * File: Starter Class - Implementation file
 * Description: Starting class. It allows us to format and validate the data entered 
 * by the user before transporting it to the distribution class.
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

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

// Description: Basic three-argument constructor.
Starter::Starter(string current_path, int argument_count, char* argument_values[])
    : current_path{current_path},
    argument_count{argument_count},
    argument_values{argument_values} {
    }

// Description: It allows us to move the received content to a more "friendly" container, in this case a container of type 'vector'.
void Starter::input_formatter(vector<string>& arg_container) {
    std::copy(argument_values, argument_values + argument_count, std::back_inserter(arg_container));
}

// Description: It allows us to identify if the emi repository is valid and... 
// if the current path from where the actions are being requested / executed is a valid path.
void Starter::startup_validator(int& validation_result) {
    // We manually build the paths of the emi repository and the emi configuration file.
    // Note: Once the control has passed to the Manager class, the paths will be built automatically.
    string emi_default_path = current_path + "/" + emi_path;
    string config_main_file = emi_default_path + "/" + config_path + "/" + config_main;

    // We validate the existence of both paths.
    if (fs::exists(emi_default_path) && fs::exists(config_main_file)) {
        validation_result = validation_codes::emi_and_path_valid;
    } else {
        // We extract the "items" or names of each directory inside the variable "current_path".
        // That means that if we have the path /usr/test/first-test/
        // The value of the items after they have been processed will be: usr, test, first-test.
        Helper helper;
        vector<string> extracted_items;
        helper.items_extractor(extracted_items, current_path, '/');

        // We iterate over the extracted items and use them to build incremental paths.
        // This means that if we have the items: usr, test, first-test and we start to "put them together"...
        // we will have the following values: /usr/, /usr/test/, /usr/test/fisrt-test.
        string temporal_path;
        vector<string> incremental_paths;
        for(size_t iterA = 1; iterA < extracted_items.size(); iterA++) {
            temporal_path += "/" + extracted_items[iterA];
            if (iterA > 0) { incremental_paths.push_back(temporal_path); }
        }

        // We order the built paths according to their length.
        std::sort(incremental_paths.begin(), incremental_paths.end(), [](const string& first, const string& second) { 
                return first.size() > second.size(); });

        bool contains_emi_path = false;
        for (const string& evaluation_path : incremental_paths) {
            // We iterate over each path stored in 'incremental_paths'.
            for (const auto& file_or_folder : fs::directory_iterator(evaluation_path)) {
                // We must remember that some constructed paths will contain a file.
                if(fs::is_directory(file_or_folder)) {
                    string folder = file_or_folder.path().string();
                    // We validate that the evaluated path contains the path of the 'emi_path'.
                    // This way we make sure that the request (the command) has been executed from a sub-folder within a tracked project.
                    // That is, the emi repository exists at a higher level and the call is being made from a lower level.
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

