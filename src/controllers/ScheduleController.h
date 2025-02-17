#pragma once

#include <models/Schedule.h>
#include "JsonWriter.h"
#include "Printer.h"
#include "TrainBuilder.h"

class ScheduleController
{

public:

    static Train addTrain( Schedule& schedule, const std::string trainName, const TrainType trainType = PASSENGER){
        Train newTrain = TrainBuilder::buildTrain(schedule, trainName, trainType);
        schedule.trains.insert({newTrain.number, newTrain});
        std::cout << "Train number [" << newTrain.number << "] added." << std::endl;
        return newTrain;
    };

    static bool removeTrain(Schedule& schedule, const int trainNumber)
    {
        auto it = schedule.trains.find(trainNumber);
        if (it != schedule.trains.end()) {
            schedule.deleted_trains.insert(it->first);
            std::cout << "Train number " << trainNumber << " removed." << std::endl;
            return true;
        } 
        
        std::cout << "Train number " << trainNumber << " not found." << std::endl;
        return false;
    };
    
    static bool addStationToRoute( Schedule& schedule, const int trainNumber, const Station& station)
    {
        if (schedule.deleted_trains.count(trainNumber) > 0) {
            std::cout << "Train number " << trainNumber << " has been removed." << std::endl;
            return false;
        } 

        if (schedule.train_routes.find(trainNumber) == schedule.train_routes.end()) {
            schedule.train_routes.insert({trainNumber, std::vector<Station>()});
        }

        schedule.train_routes.at(trainNumber).push_back(station);
        std::cout << "Station " << station.name << " added to train number " << trainNumber << "'s route." << std::endl;
        return true;
    };



    static void displaySchedule(const Schedule& schedule)
    {
        std::cout << "::::::::::::: Schedule ::::::::::::::" << std::endl;
        for (const auto& [number, train] : schedule.trains) {
            Printer::print(schedule, number);
            std::cout << "-------------------------------" << std::endl;
        }
    };



    static void writeScheduleToJson(const Schedule& schedule, const std::string& filename)
    {
        JsonWriter::writeScheduleToFile(schedule, filename);
    };

    static bool queryTrain(Schedule& schedule, const int trainNumber)
    {
        if (schedule.deleted_trains.count(trainNumber) > 0) {
            std::cout << "Train number " << trainNumber << " has been removed." << std::endl;
            return false;
        } 

        auto it = schedule.trains.find(trainNumber);
        if (it != schedule.trains.end()) {
            Printer::print(schedule, it->first);
            return true;
        } 

        std::cout << "Train number " << trainNumber << " not found." << std::endl;
        return false;
    };

    static void queryTrainSource(Schedule& schedule, const std::string sourceStation)
    {
        for (const auto& [number, stations] : schedule.train_routes) {
            if (stations.size() > 0 && stations.front().name == sourceStation) {
                Printer::print(schedule, number);
            }
        }        
    };

    static void queryTrainDestination(Schedule& schedule, const std::string destinationStation)
    {
        for (const auto& [number, stations] : schedule.train_routes) {
            if (stations.size() > 0 && stations.back().name == destinationStation) {
                Printer::print(schedule, number);
            }
        }        
    };

    static void queryTrainDeparture(Schedule& schedule, const std::string departuretime)
    {
        for (const auto& [number, times] : schedule.train_departures) {
            for (const auto& time : times) {
                if (time.time == departuretime) {
                    Printer::print(schedule, number);
                }
            }
        }        
    };
};

