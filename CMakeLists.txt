CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(flock LANGUAGES CXX HOMEPAGE_URL https://github.com/yosmont/falloutLock)
INCLUDE(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncurses -Wall -Wextra")
ADD_EXECUTABLE(flock
    src/RandomWordAPI.cpp
    src/ConsoleBuffer.cpp
    src/FLockDisplay.cpp
    src/FLock.cpp
    src/main.cpp)
TARGET_LINK_LIBRARIES(flock PRIVATE ncurses cpr::cpr)
TARGET_INCLUDE_DIRECTORIES(flock PRIVATE src submodules/json/single_include)