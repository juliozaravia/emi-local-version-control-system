/*
 * Project: EMI Personal Control Version System 
 * File: Builder Class - Definition file 
 * Description: Clase de ejecución. Nos permite realizar las acciones principales como
 * creación, registro, eliminado y transporte de directorios y/o archivos entre otras acciones
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

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
    template <typename T>
    void directory_builder(const T&);
    
    // Cleaners
    void data_cleaner(const std::string&);
    
    // Catchers & Savers
    template <typename T>
    void data_catcher(const T&, const std::string&);
    void data_saver(const std::vector<std::string>&, const std::string&, const std::string&, const std::string&, const std::string&);
    
    // Inserters
    template <typename T>
    void data_inserter(const T&, const std::string&);
    
    // Removers
    void repository_remover(const std::string&, int);
    template <typename T>
    void file_remover(const T&, int = 0);
    
    // Transporters
    template <typename T>
    void file_transporter(const T&, const std::string&, const std::string& = std::string());
    void special_transporter(const std::vector<std::string>&, const std::vector<std::string>&); 

    // Others
    void file_renamer(const std::string&, const std::string&, const std::string&);

    virtual ~Builder();
};

#endif // BUILDER_H

