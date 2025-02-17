#pragma once

#include <models/Schedule.h>
#include <models/Train.h>


class TrainBuilder
{
public:
   static Train buildTrain(const Schedule& schedule, const std::string& trainName, const TrainType trainType)
   {
       int trainIndex = schedule.trains.size() + 1;
       Train newTrain{trainIndex, trainType, trainName};
       return newTrain;
   };
};

