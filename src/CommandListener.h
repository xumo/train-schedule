#pragma once
#include <string>

#include <models/Schedule.h>      

class CommandListener {
public:
    CommandListener(Schedule& schedule) : schedule(schedule) {}
    void listen();

private:
    Schedule& schedule;
    bool parseCommand(const std::string& input);
    void printHelp();
};
