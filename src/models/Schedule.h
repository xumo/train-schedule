#pragma once

#include <map>
#include <set>
#include <vector>
#include "Station.h"
#include "TimePoint.h"
#include "Train.h"


struct Schedule
{
    std::map<int, Train> trains;
    std::set<int> deleted_trains;
    std::map<int, std::vector<Station>> train_routes;
    std::map<int, std::vector<TimePoint>> train_departures;
};
