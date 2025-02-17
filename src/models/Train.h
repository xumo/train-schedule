#pragma once
#include <string>
#include <vector>

#include "Station.h"

enum TrainType
{
    PASSENGER,
    FREIGHT
};

struct Train
{
    const int number;
    const TrainType type;
    const std::string name;
};
