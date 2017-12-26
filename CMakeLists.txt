cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(src/client/lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
include_directories(/tests)
include_directories(/include)
include_directories(/src)
include_directories(/server)

set(SOURCE_FILES ./src/client/include/Board.h ./src/client/src/Board.cpp ./src/client/src/Point.cpp ./src/client/include/Point.h
        ./src/client/src/Cell.cpp ./src/client/include/Cell.h ./src/client/include/GameLogic.h ./src/client/src/BasicLogic.cpp
        ./src/client/include/BasicLogic.h ./src/client/include/Player.h ./src/client/src/HumanPlayer.cpp ./src/client/include/HumanPlayer.h
        ./src/client/src/GameFlow.cpp ./src/client/include/GameFlow.h ./src/client/src/CellCounter.cpp ./src/client/include/CellCounter.h
        ./src/client/src/Menu.cpp ./src/client/include/Menu.h ./src/client/src/AIPlayer.cpp ./src/client/include/AIPlayer.h
        ./src/client/src/RemoteGame.cpp ./src/client/include/RemoteGame.h)
add_executable(ex1 ${SOURCE_FILES} ./src/client/src/main.cpp)

set(SOURCE_FILES_TEST ./src/client/include/Board.h ./src/client/src/Board.cpp ./src/client/src/Point.cpp ./src/client/include/Point.h
        ./src/client/src/Cell.cpp ./src/client/include/Cell.h ./src/client/include/GameLogic.h ./src/client/src/BasicLogic.cpp
        ./src/client/include/BasicLogic.h ./src/client/include/Player.h ./src/client/src/HumanPlayer.cpp
        ./src/client/include/HumanPlayer.h ./src/client/src/GameFlow.cpp ./src/client/include/GameFlow.h ./src/client/src/CellCounter.cpp
        ./src/client/include/CellCounter.h ./src/client/src/Menu.cpp ./src/client/include/Menu.h ./src/client/src/AIPlayer.cpp
        ./src/client/include/AIPlayer.h ./src/client/tests/gtest_main.cpp ./src/client/tests/test_BasicLogic.cpp
        ./src/client/tests/test_AIPlayer.cpp ./src/client/tests/test_Board.cpp)
add_executable(ReversiTest ${SOURCE_FILES_TEST} ${SOURCE_FILES})
target_link_libraries(ReversiTest gtest gtest_main)

set(SERVER_SRC_FILES ./src/server/Server.cpp ./src/server/Server.h)
add_executable(server ${SERVER_SRC_FILES} ./src/server/main.cpp)