#pragma once

#include <nlohmann/json.hpp>
#include <models/Schedule.h>
#include <models/Train.h>
#include <models/Station.h>
#include <models/TimePoint.h>

class JsonParser
{
public:

    static Schedule jsonToSchedule(const std::string& jsonString){
        nlohmann::json j = nlohmann::json::parse(jsonString);
        Schedule schedule;
        for (const auto& item : j["trains"].items()) {
            int id = std::stoi(item.key());
            auto train_node = item.value();
            std::cout << "node: " << train_node.dump() << std::endl;
            Train train = JsonParser::train_json(train_node);
            schedule.trains.insert({train.number, train});
        }
        auto deleted_trains_node = j["deleted_trains"];
        if (!deleted_trains_node.is_null()) {
            schedule.deleted_trains = j["deleted_trains"].get<std::set<int>>();
        }
        auto train_routes_node = j["train_routes"];
        if (!train_routes_node.is_null()) {
            for (const auto& item : train_routes_node.items()) {
                int id = std::stoi(item.key());
                std::cout << "route: " << item.value().dump() << std::endl;
                schedule.train_routes.insert({id, JsonParser::stations_json(item.value())}) ;
            }
        }

        auto train_departures_node = j["train_departures"];
        if (!train_departures_node.is_null()) {
            for (const auto& item : train_departures_node.items()) {
                int id = std::stoi(item.key());
                schedule.train_departures[id] = timePoints_json(item.value());
            }
        }

        return schedule;
    };

    static Train train_json(const nlohmann::json& j) {
        int number = j.at("number");
        TrainType type =  j.at("type") == "PASSENGER" ? PASSENGER : FREIGHT;
        std::string name = j.at("name");
        Train t{number, type, name};
        return t;
    }

    static Station station_json(const nlohmann::json& j) {
        if (j.is_null()) {
            return Station{"", ""};
        }

        if (!j.contains("name")) {
            return Station{"", ""};
        }   
        std::string name = j.at("name");
        std::string location = j.contains("location") ? j.at("location") : "";
        Station s{name, location};
        return s;
    }

    static TimePoint timePoint_json(const nlohmann::json& j) {
        std::string time = j.at("time");
        TimePoint tp{time};
        return tp;
    }

    static std::vector<Station> stations_json(const nlohmann::json& j) {
        std::vector<Station> stations;
        for (const auto& item : j) {
            stations.push_back(station_json(item));
        }
        return stations;
    }

    static std::vector<TimePoint> timePoints_json(const nlohmann::json& j) {
        std::vector<TimePoint> timePoints;
        for (const auto& item : j) {
            timePoints.push_back(timePoint_json(item));
        }
        return timePoints;
    }

};

