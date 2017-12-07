cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(/tests)
include_directories(/include)
include_directories(/src)

set(SOURCE_FILES ./include/Board.h ./src/Board.cpp ./src/Point.cpp ./include/Point.h ./src/Cell.cpp ./include/Cell.h
        ./include/GameLogic.h ./src/BasicLogic.cpp ./include/BasicLogic.h ./include/Player.h
        ./src/HumanPlayer.cpp ./include/HumanPlayer.h ./src/GameFlow.cpp ./include/GameFlow.h ./src/CellCounter.cpp ./include/CellCounter.h
        ./src/Menu.cpp ./include/Menu.h ./src/AIPlayer.cpp ./include/AIPlayer.h ./src/RemoteGame.cpp ./include/RemoteGame.h)
add_executable(ex1 ${SOURCE_FILES} main.cpp)

set(SOURCE_FILES_TEST ./include/Board.h ./src/Board.cpp ./src/Point.cpp ./include/Point.h ./src/Cell.cpp ./include/Cell.h
        ./include/GameLogic.h ./src/BasicLogic.cpp ./include/BasicLogic.h ./include/Player.h
        ./src/HumanPlayer.cpp ./include/HumanPlayer.h ./src/GameFlow.cpp ./include/GameFlow.h ./src/CellCounter.cpp ./include/CellCounter.h
        ./src/Menu.cpp ./include/Menu.h ./src/AIPlayer.cpp ./include/AIPlayer.h tests/gtest_main.cpp tests/test_BasicLogic.cpp tests/test_AIPlayer.cpp tests/test_Board.cpp
        ./src/RemoteGame.cpp ./include/RemoteGame.h)
add_executable(ReversiTest ${SOURCE_FILES_TEST} ${SOURCE_FILES})
target_link_libraries(ReversiTest gtest gtest_main)