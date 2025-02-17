#include <gtest/gtest.h>

#include <models/Schedule.h>
#include <controllers/JsonParser.h>
#include <controllers/Printer.h>
#include <controllers/ScheduleController.h>

// Demonstrate some basic assertions.
TEST(ScheduleTest, ScheduleJson) {
    auto input_string = R"({
    "trains": {
        "1": {
        "number": 1,
        "name": "Express 101",
        "type": "PASSENGER"
        },
        "2": {
        "number": 2,
        "name": "Local 202",
        "type": "PASSENGER"
        },
        "3": {
        "number": 3,
        "name": "Regional 303",
        "type": "PASSENGER"
        },
        "4": {
        "number": 4,
        "name": "Freight 404",
        "type": "FREIGHT"
        }
    },
    "train_routes": {
        "1": [
        {
            "id": 1,
            "name": "Central Station"
        },
        {
            "id": 2,
            "name": "North Station"
        },
        {
            "id": 3,
            "name": "East Station"
        }
        ],
        "2": [
        {
            "id": 4,
            "name": "South Station"
        },
        {
            "id": 5,
            "name": "Old Town Station"
        },
        {
            "id": 6,
            "name": "New Town Station"
        }
        ],
        "3": [
        {
            "id": 7,
            "name": "Airport Station"
        },
        {
            "id": 8,
            "name": "University Station"
        },
        {
            "id": 9,
            "name": "Business District Station"
        }
        ],
        "4": [
        {
            "id": 10,
            "name": "Mountain Station"
        },
        {
            "id": 11,
            "name": "Valley Station"
        },
        {
            "id": 12,
            "name": "River Station"
        }
        ]
    },
    "train_departures": {
        "1": [
        {
            "time": "09:30"
        },
        {
            "time": "15:45"
        }
        ],
        "2": [
        {
            "time": "07:15"
        },
        {
            "time": "12:00"
        }
        ],
        "3": [
        {
            "time": "10:00"
        },
        {
            "time": "18:30"
        }
        ],
        "4": [
        {
            "time": "06:45"
        },
        {
            "time": "14:15"
        }
        ]
    }
    })";

    Schedule schedule = JsonParser::jsonToSchedule(input_string);
    ScheduleController::displaySchedule(schedule);

}