cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp ./include/Board.h ./src/Board.cpp ./src/Point.cpp ./include/Point.h ./src/Cell.cpp ./include/Cell.h ./include/GameLogic.h ./src/BasicLogic.cpp ./include/BasicLogic.h ./include/Player.h ./src/HumanPlayer.cpp ./include/HumanPlayer.h ./src/GameFlow.cpp ./include/GameFlow.h ./src/CellCounter.cpp ./include/CellCounter.h ./src/Menu.cpp ./include/Menu.h ./src/AIPlayer.cpp ./include/AIPlayer.h tests/gtest_main.cpp tests/test_BasicLogic.cpp)
add_executable(ex1 ${SOURCE_FILES})