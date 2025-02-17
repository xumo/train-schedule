#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <models/Schedule.h>
#include <models/Station.h>
#include <models/TimePoint.h>
#include <models/Train.h>


class Printer {

public:

    static void print(const Schedule& schedule, const int trainNumber) {
        auto it = schedule.trains.find(trainNumber);
        if (it != schedule.trains.end()) {
            print(it->second);
            auto routes = schedule.train_routes.find(trainNumber);
            if (routes != schedule.train_routes.end()) {
                std::cout << "Route: ";
                print(routes->second);
            }
            auto departures = schedule.train_departures.find(trainNumber);
            if (departures != schedule.train_departures.end()) {
                std::cout << "Departures: " << std::endl;
                print(departures->second);
            }
        } else {
            std::cout << "Train number " << trainNumber << " not found." << std::endl;
        }
    }

    static void print(const Train& train) {
        std::cout << "Train " << std::endl;
        std::cout << "  - Number: " << train.number << std::endl;
        std::cout << "  - Name: " << train.name << std::endl;
        std::cout << "  - Type: " << (train.type == PASSENGER ? "Passenger" : "Freight")  << std::endl;
    }

    static void print(const std::vector<Station>& stations) {
        std::cout << "Station: " << std::endl;
        for (const auto& station : stations) {
            std::cout << "  - Name: " << station.name << std::endl;
            std::cout << "  - Location: " << station.location << std::endl;
        }
    }
    
    static void print(const std::vector<TimePoint>& times) {
        for (const auto& time : times) {
            std::cout << "  - " << time.time << std::endl;
        }
    }
};
