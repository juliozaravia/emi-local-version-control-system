#ifndef HELPER_H
#define HELPER_H

#include <unordered_map>

#include "Structures.h"

class Helper {
    private:
        Base base;

    public:
        Helper();
        // Comparators
        bool hash_comparator(const std::vector<std::string>&, const struct File&);

        // Extractors
        std::string row_extractor(const std::string&, const std::string&);
        void rows_extractor(std::vector<std::string>&, const std::string&, const std::string& = std::string());
        void items_extractor(std::vector<std::string>&, const std::string&, char = ',');
        void items_extractor(std::vector<std::string>&, const std::string&, int);

        // Checkers
        bool content_checker(const std::string&);
        bool ignored_file_checker(const std::string&, const std::string&);
        template<typename T> 
        bool existence_checker(const T&, const std::string&);

        // Generators
        unsigned int hash_generator(const std::string&);
        void timepoint_generator(std::string&);

        // Organizers
        void data_organizer(struct File&, const std::string&);
        void data_organizer(std::vector<File>&, const std::vector<std::string>&, int);
        template<typename T> 
        void data_organizer(std::vector<File>&, const T&);
        void available_files_organizer(std::unordered_map<std::string,std::string>&,
                const std::vector<std::string>&,
                const std::string&);
        void available_files_organizer(std::vector<std::string>&,
                std::vector<std::string>&,
                const std::vector<std::string>&,
                const std::string&);
        void available_files_folders_organizer(std::vector<std::string>&, std::vector<std::string>&, const std::vector<std::string>&, const std::string&); 
        void processed_files_organizer(std::vector<std::string>&,
                std::vector<std::string>&,
                const std::unordered_map<std::string,std::string>&,
                const std::unordered_map<std::string,std::string>&,
                const std::string&);
        void log_organizer(struct Log&, std::vector<Log>&,
                std::unordered_multimap<std::string,std::string>&,
                const std::vector<std::string>&);
        void status_organizer(std::unordered_map<std::string,std::string>&,
                std::unordered_map<std::string,std::string>&,
                std::unordered_map<std::string,std::string>&,
                const std::string&);
        // decepti0n
        void deception(std::vector<File>&, const std::string&, const std::string&, const std::vector<std::string>&);

        virtual ~Helper();
};

#endif // HELPER_H

