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

Starter::Starter(string current_path, int argument_count, char* argument_values[])
    : current_path{current_path},
    argument_count{argument_count},
    argument_values{argument_values} {
    }

void Starter::input_formatter(vector<string>& arg_container) {
    std::copy(argument_values, argument_values + argument_count, std::back_inserter(arg_container));
}

void Starter::startup_validator(int& validation_result) {
    string emi_default_path = current_path + "/" + emi_path;
    string config_main_file = emi_default_path + "/" + config_path + "/" + config_main;
    
    if (fs::exists(emi_default_path) && fs::exists(config_main_file)) {
        validation_result = validation_codes::emi_and_path_valid;
    } else {
        Helper helper;
        vector<string> extracted_items;
        helper.items_extractor(extracted_items, current_path, '/');

        string temporal_path;
        vector<string> full_paths;
        for(size_t iterA = 1; iterA < extracted_items.size(); iterA++) {
            temporal_path += "/" + extracted_items[iterA];
            if (iterA > 0) { full_paths.push_back(temporal_path); }
        }

        std::sort(full_paths.begin(), full_paths.end(), [](const std::string& first, const std::string& second){
                return first.size() > second.size();
                });

        bool match_counter = false;
        for (const string& eval_path : full_paths) {
            for (const auto& file_or_folder : fs::directory_iterator(eval_path)) {
                if(fs::is_directory(file_or_folder)) {
                    string folder = file_or_folder.path().string();
                    if (folder.find(emi_path) != string::npos) {
                        match_counter = true;
                        break;
                    }
                }
            }
            if (match_counter) { break; }
        }

        if (!match_counter) {
            validation_result = validation_codes::emi_and_path_not_valid;
        } else {
            validation_result = validation_codes::emi_valid_path_not_valid;
        }
    }
}

Starter::~Starter() {}

