cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(/tests)

set(SOURCE_FILES Board.h Board.cpp Point.cpp Point.h Cell.cpp Cell.h GameLogic.h BasicLogic.cpp
        BasicLogic.h Player.h
        HumanPlayer.cpp HumanPlayer.h GameFlow.cpp GameFlow.h CellCounter.cpp
        CellCounter.h Menu.cpp Menu.h AIPlayer.cpp AIPlayer.h)
add_executable(ex1 ${SOURCE_FILES} main.cpp)

set(SOURCE_FILES_TEST Board.h Board.cpp Point.cpp Point.h Cell.cpp Cell.h GameLogic.h BasicLogic.cpp
        BasicLogic.h Player.h
        HumanPlayer.cpp HumanPlayer.h GameFlow.cpp GameFlow.h CellCounter.cpp
        CellCounter.h Menu.cpp Menu.h AIPlayer.cpp AIPlayer.h tests/gtest_main.cpp tests/test_BasicLogic.cpp)
add_executable(ReversiTest ${SOURCE_FILES_TEST} ${SOURCE_FILES})
target_link_libraries(ReversiTest gtest gtest_main)