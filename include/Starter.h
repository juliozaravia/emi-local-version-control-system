/*
 * Project: EMI Personal Control Version System 
 * File: Starter Class - Definition file 
 * Description: Clase de arranque. Nos permite formatear y validar la data
 * ingresada por el usuario antes de transportarla a la clase de distribución
 * @author
 * Julio Zaravia <hello@juliozaravia.com>
 */

#ifndef STARTER_H
#define STARTER_H

#include <string>
#include <vector>

class Starter {
private:
    std::string current_path;
    int argument_count;
    char** argument_values;

public:
    Starter(std::string, int, char* []);
    void input_formatter(std::vector<std::string>&);
    void startup_validator(int&);

    virtual ~Starter();
};

#endif // STARTER_H

