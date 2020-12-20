/*
 * Project: Emi Local Version Control System 
 * File: Starter Class - Definition file 
 * Description: Starting class. It allows us to format and validate the data entered 
 * by the user before transporting it to the distribution class.
 * @author
 * Julio Zaravia <hey@juliozaravia.com>
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

