#include "CommandListener.h"

#include <models/Schedule.h>    
#include <controllers/ScheduleController.h>  

#include <iostream>
#include <sstream>

void CommandListener::listen() {
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "exit") {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        if (!parseCommand(input) && input != "help") {
            printHelp();
        }
    }
}

void CommandListener::printHelp() {
    std::cout << ":::::::::: Commands available ::::::::::" << std::endl;
    std::cout << "add train \"<name>\" <type:PASSENGER|FREIGHT>" << std::endl;
    std::cout << "add station <train_number> \"<name>\" \"<location>\"" << std::endl;
    std::cout << "remove train <number>" << std::endl;
    std::cout << "query source \"<station_name>\"" << std::endl;
    std::cout << "query destination \"<station_name>\"" << std::endl;
    std::cout << "query departure <time>" << std::endl;
    std::cout << "display schedule" << std::endl;
    std::cout << "display train <number>" << std::endl;
    std::cout << "save <filename.json>" << std::endl;
    std::cout << "exit" << std::endl;
    std::cout << "::::::::::::::::::::::::::::::::::::::::" << std::endl;
}

bool CommandListener::parseCommand(const std::string& input) {
    std::istringstream iss(input);
    std::string command;
    iss >> command;
    if (command == "add") {
        std::string type;
        iss >> type;
        
        if (type == "train" && input.size() > 10) {
            std::string name;
            iss.ignore();
            std::getline(iss, name, '"'); 
            std::getline(iss, name, '"'); 

            std::string inputCopy = input;
            std::transform(inputCopy.begin(), inputCopy.end(), inputCopy.begin(), ::toupper);
            
            TrainType trainType = (inputCopy.find("FREIGHT") != std::string::npos) ? TrainType::FREIGHT : TrainType::PASSENGER;
            
            if (name.find("FREIGHT") != std::string::npos) {
                name = name.replace(name.find("FREIGHT"), 7, "");
            } else if (name.find("PASSENGER") != std::string::npos) {
                name = name.replace(name.find("PASSENGER"), 9, "");
            }
      
            ScheduleController::addTrain(schedule, name, trainType);
            return true;
        } else if (type == "station") {
            int trainNumber;
            iss >> trainNumber;
            std::string name;
            iss.ignore();
            std::getline(iss, name, '"'); 
            std::getline(iss, name, '"'); 
            std::string location;
            iss.ignore();
            std::getline(iss, location, '"');
            std::getline(iss, location, '"');
            bool ok = ScheduleController::addStationToRoute(schedule, trainNumber, Station{name, location});
            return ok;
        }
    } else if (command == "remove") {
        std::string type;
        int number;
        iss >> type >> number;
        if (type == "train") {
            bool ok = ScheduleController::removeTrain(schedule, number);
            return ok;
        }
    } else if (command == "query") {
        std::string type, name;
        iss >> type >> name;
        bool ok = true;
        if (type == "source") {
            ScheduleController::queryTrainSource(schedule, name);
        } else if (type == "destination") {
            ScheduleController::queryTrainDestination(schedule, name);
        } else if (type == "departure") {
            ScheduleController::queryTrainDeparture(schedule, name);
        } else {
            ok = false;
        }
        return ok;
    } else if (command == "display") {
        std::string type;
        int number;
        iss >> type >> number;
        if (type == "schedule") {
            ScheduleController::displaySchedule(schedule);
            return true;
        } else if (type == "train") {
            ScheduleController::queryTrain(schedule, number);
            return true;
        }
    } else if (command == "save") {
        std::string filename;
        iss >> filename;
        if (filename.find(".json") != std::string::npos) {
            ScheduleController::writeScheduleToJson(schedule, filename);
            return true;
        } 
    }  else if (command == "help") {
        printHelp();
        return true;
    }  else {
        std::cout << "Invalid command [[" << input << "]] "  << std::endl;
    }

    return false;
}
