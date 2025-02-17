#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "models/Train.h"
#include "models/Station.h"
#include "models/Schedule.h"
#include "CommandListener.h"

#include <controllers/JsonWriter.h>
#include <controllers/JsonParser.h>
#include <controllers/Printer.h>
#include <controllers/ScheduleController.h>

int main(int argc, char const *argv[])
{
    Schedule schedule;
    if (argc > 1) {
        std::string input = argv[1];
        std::cout << "Reading file from: " << input << std::endl;
        std::ifstream file(input);
        if (file.is_open()) {
            std::string line;
            std::string json;
            while (std::getline(file, line)) {
                json += line;
            }
            file.close();
            schedule = JsonParser::jsonToSchedule(json);
            ScheduleController::displaySchedule(schedule);
        } else {
            std::cout << "Unable to open file." << std::endl;
        }
    }

    CommandListener listener(schedule);
    listener.listen();

    return 0;
}
