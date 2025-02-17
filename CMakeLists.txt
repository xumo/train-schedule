cmake_minimum_required(VERSION 3.24)

project(TrainSchedule)

set(CMAKE_CXX_STANDARD 17)
# include_directories(src/models)
# include_directories(src/controllers)
include_directories(src)


file(GLOB SOURCES "src/*.cpp" "src/models/*.cpp" "src/controllers/*.cpp")

add_executable(TrainSchedule ${SOURCES})

# Include nlohmann_json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)


# Link nlohmann_json to the main executable
target_link_libraries(TrainSchedule nlohmann_json::nlohmann_json)

include(FetchContent)
# Download and configure Google Test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories(nlohmann_json)
# Add test executable
file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(TrainScheduleTests ${TEST_SOURCES})
add_executable(TrainTest tests/train_test.cpp) 


target_link_libraries(TrainScheduleTests gtest gtest_main)
target_link_libraries(TrainScheduleTests nlohmann_json::nlohmann_json)


target_link_libraries(TrainTest gtest gtest_main)
target_link_libraries(TrainTest nlohmann_json::nlohmann_json)

# Enable testing
enable_testing()

# Add tests
add_test(NAME TrainScheduleTests COMMAND TrainScheduleTests)
add_test(NAME TrainTest COMMAND TrainTest)

# include(GoogleTest)
# gtest_discover_tests(TrainScheduleTests)



