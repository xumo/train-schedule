#pragma once

#include <iostream>
#include <models/Schedule.h>
#include <nlohmann/json.hpp>
#include <fstream>

class JsonWriter
{

public:
    static nlohmann::json scheduleToJson(const Schedule& schedule){
        nlohmann::json j;
        j["trains"] = trainsToJson( schedule.trains);
        j["deleted_trains"] = schedule.deleted_trains;
        j["train_routes"] = routesToJson(schedule.train_routes);
        j["train_departures"] = departuresToJson(schedule.train_departures);
        return j;
    };

    static nlohmann::json timePointsToJson(const std::vector<TimePoint>& timePoints){
        nlohmann::json j;
        for (const auto& timePoint : timePoints) {
            j.push_back(timePointToJson(timePoint));
        }
        return j;
    };

    static nlohmann::json timePointToJson(const TimePoint& timePoint){
        nlohmann::json j;
        j["time"] = timePoint.time;
        return j;
    };

    static nlohmann::json stationToJson(const Station& station){
        nlohmann::json j;
        j["name"] = station.name;
        j["location"] = station.location;
        return j;
    };

    static nlohmann::json trainToJson(const Train& train){
        nlohmann::json j;
        j["number"] = train.number;
        j["type"] = train.type == PASSENGER ? "PASSENGER" : "FREIGHT";
        j["name"] = train.name;
        return j;
    };


    static nlohmann::json routesToJson(const std::map<int, std::vector<Station>>& train_routes){
        nlohmann::json j;
        for (const auto& route : train_routes) {
            j[std::to_string(route.first)] = stationsToJson(route.second);
        }
        return j;
    };

    static nlohmann::json departuresToJson(const std::map<int, std::vector<TimePoint>>& train_departures){
        nlohmann::json j;
        for (const auto& departure : train_departures) {
            j[std::to_string(departure.first)] = timePointsToJson(departure.second);
        }
        return j;
    };

    static nlohmann::json stationsToJson(const std::vector<Station>& stations){
        nlohmann::json j;
        for (const auto& station : stations) {
            j.push_back(stationToJson(station));
        }
        return j;
    };

    static nlohmann::json trainsToJson(const std::map<int, Train>& trains){
        nlohmann::json j;
        for (const auto& train : trains) {
            j[std::to_string(train.first)] = trainToJson(train.second);
        }
        return j;
    };

    static void writeScheduleToFile(const Schedule& schedule, const std::string& filename){
        nlohmann::json j = scheduleToJson(schedule);
        std::ofstream file(filename);
        file << j.dump(4);
        file.close();
    };
};

