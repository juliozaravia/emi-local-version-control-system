#ifndef BUILDER_H
#define BUILDER_H

#include "Structures.h"

class Builder {
private:
    Base base;

public:
    Builder();
    Builder(struct Base);
    // Builders
    void repository_builder(const std::string& current_path);
    // Cleaners
    //void version_cleaner(const std::vector<std::string>&, const std::vector<std::string>&);
    //void version_cleaner(const std::vector<File>&);
    void data_cleaner(const std::string&);
    // Catchers & Savers
    template <typename T>
    void data_catcher(const T&, const std::string&, const std::string&);
    //void version_catcher(const struct File&);
    //void version_catcher(const std::vector<File>&);
    void file_renamer(const std::string&, const std::string&, const std::string&);
    void data_saver(const std::vector<std::string>&, const std::string&, const std::string&, const std::string&);
    // Inserters
    template <typename T>
    void data_inserter(const T&, const std::string&);
    //void data_inserter(const std::string&, const std::string&);
    //void data_inserter(const std::vector<std::string>&);
    // Removers
    void repository_remover(const std::string&, int);
    template <typename T>
    void file_remover(const T&, const std::string&);
    //void version_remover(const std::string&);
    //void version_remover(const std::vector<std::string>&);
    // Others
    void file_transporter(const std::vector<std::string>&, const std::string&, const std::string&, const std::string&);
    //void version_transporter(const std::vector<File>&, const std::string&);

    virtual ~Builder();
};

#endif // BUILDER_H

