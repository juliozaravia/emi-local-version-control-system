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
        bool hash_comparator(const std::string&, const unsigned int&);

        // Extractors
        std::string row_extractor(const std::string&, const std::string&);
        void rows_extractor(std::vector<std::string>&, const std::string&, const std::string& = std::string(), int = 0, int = 0);
        void items_extractor(std::vector<std::string>&, const std::string&, char = ',');
        template<typename T,typename U>
        void content_extractor(T&, const U&, int);

        // Checkers
        bool content_checker(const std::string&);
        bool ignored_file_checker(const std::string&, const std::string&);
        template<typename T> 
        bool existence_checker(const T&, std::unordered_map<std::string,bool>&);

        // Generators
        std::string location_generator(const std::string&, const std::string&); 
        unsigned int hash_generator(const std::string&, int);
        void timepoint_generator(std::string&);
        void compound_name_generator(const std::string&, std::vector<std::string>&);

        // Organizers
        void data_organizer(struct File&, const std::string&, const std::string&);
        template<typename T, typename U>
        void data_organizer(T&, const U&, const std::string&, int = 0);
        template<typename T> 
        void data_organizer(std::vector<File>&, const T&, const std::string&);
        void availability_organizer(std::unordered_map<std::string,std::string>&,
                const std::vector<std::string>&,
                const std::string&);
        void availability_organizer(std::vector<std::string>&, std::vector<std::string>&, const std::vector<std::string>&, const std::string&); 
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
        void duplicate_organizer(std::vector<std::string>&);

        virtual ~Helper();
};

#endif // HELPER_H

