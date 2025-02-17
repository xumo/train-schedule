# Train schedule
Author: Rodrigo Torres González


## Requirements
In order to build this projes this is at lest the requirements:
- A modern C++ compiler with at least C++17 support.
- CMake version 3.24
- Internet conexcion to download 3rd party dependencies.

## Build
To build the application in a Unix like system (Linux, MAc, etc.) run these commands in a terminal in the project directory:

```bash
mkdir build
cd build
cmake ..
make
./TrainSchedule ../schedule.json
```

In Windows with Visual Studio and it's build tools installed:

```powershell
mkdir build
cd build
msbuild .\TrainSchedule.sln
# or for release 
msbuild .\TrainSchedule.sln /p:Configuration=Release
.\Debug\TrainSchedule.exe ..\schedule.json
```
The program accepts an argument to load a Schedule in JSON format, a sample is provided in `schedule.json`.


### Running the app
The application can load a JSON file that is passed as an argument;otherwise, it starts with an empty Schedule.
Enter input commands by typing + enter, `help` prints a list of available commands.
These are the ones expected:
- `add train "<name>" <type:PASSENGER|FREIGHT>`
- `add station <train_number> "<name>" "<location>"`
- `remove train <number>`
- `query source "<station_name>"`
- `query destination "<station_name>"`
- `query departure <time>`
- `display schedule`
- `display train <number>`
- `save <filename.json>`
- `help`
- `exit`

### Tests
Some sample test were written in:
-  `tests\schedule_test.cpp`.
-  `tests\train_test.cpp`.

Both are compiled to the `TrainScheduleTests(.exe)` excecutable.

## Design Choices
The choice to use `struct` instead of classes was to force the separation of the data and the logic. I avoided creating object with method that can alter it's inner state, so I can have only one source of truth.
Having, almost, only header files makes the intent more clear: keep the side effects impact localized in a main ScheduleController.

The json data format was choosen beacause it's ubiquity in present times. It is very easy to read and write with a numerous libraries available for it.

The command line input was just for simplicity, as writting a webservice to accept the commands would have cerated an extra layer fo complexity.

## Limitations
- There is no validation for data input.
- No further tests where implemented.
- There is no error handling while file reading or  writting.
- Time is treated as string, with no validation nor convertion.
- Train Sation are not validated in any way.
- Train routes order ins not taken into account.

