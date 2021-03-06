/*
 * Project: Emi Local Version Control System 
 * File: Communicator Class - Definition file 
 * Description: Communication class. It allows us to print success, alert and error messages on the screen.
 * @author
 * Julio Zaravia <hey@juliozaravia.com>
 */

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <unordered_map>
#include <vector>

#include "Structures.h"

class Communicator {
private:

public:
    Communicator();

    void event_reporter(int, const std::string& = std::string());
    void warning_reporter(int, const std::string& = std::string());
    void error_reporter(int, const std::string& = std::string(), const char* = "");
    void command_reporter();
    void version_reporter();
    void status_reporter(const std::unordered_map<std::string,std::string>&,
                         const std::unordered_map<std::string,std::string>&,
                         const std::unordered_map<std::string,std::string>&,
                         const std::string&);
    void log_reporter(const std::vector<Log>&, const std::unordered_multimap<std::string,std::string>&, const std::string&);
    void authorization_reporter(const std::string&);

    virtual ~Communicator();
};

#endif // COMMUNICATOR_H

