#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <unordered_map>
#include <vector>

#include "Structures.h"

class Communicator {
private:

public:
    Communicator();

    void event_reporter(int com_identifier, const std::string& = std::string(), const char* = "");
    void command_reporter();
    void version_reporter();
    void status_reporter(const std::unordered_map<std::string,std::string>&,
                         const std::unordered_map<std::string,std::string>&,
                         const std::unordered_map<std::string,std::string>&,
                         const std::string&);
    void log_reporter(const std::vector<Log>&, const std::unordered_multimap<std::string,std::string>&);
    void authorization_reporter(const std::string&);

    virtual ~Communicator();
};

#endif // COMMUNICATOR_H

