#ifndef MANAGER_H
#define MANAGER_H

#include "Structures.h"

class Manager {
private:
    std::string current_path;
    std::vector<std::string> arg_container;
    Base base;

    void simple_catch_manager();
    void multiple_catch_manager();
	void simple_drop_manager();
	void multiple_drop_manager();

public:
    Manager(std::string current_path, std::vector<std::string> arg_container);
    void start_manager();
    void catch_manager();
    void drop_manager();
    void snapshot_manager();
    void look_manager();
    void log_manager();
    void ignore_manager();
    void return_manager();
    void restart_manager();
    void bye_manager();

    virtual ~Manager();
};

#endif // MANAGER_H

