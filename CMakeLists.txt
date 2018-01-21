cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS -pthread)

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
add_executable(ex1 ${SOURCE_FILES} ./src/client/src/main.cpp src/client/src/SubMenu.cpp)

set(SOURCE_FILES_TEST ./src/client/include/Board.h ./src/client/src/Board.cpp ./src/client/src/Point.cpp ./src/client/include/Point.h
        ./src/client/src/Cell.cpp ./src/client/include/Cell.h ./src/client/include/GameLogic.h ./src/client/src/BasicLogic.cpp
        ./src/client/include/BasicLogic.h ./src/client/include/Player.h ./src/client/src/HumanPlayer.cpp
        ./src/client/include/HumanPlayer.h ./src/client/src/GameFlow.cpp ./src/client/include/GameFlow.h ./src/client/src/CellCounter.cpp
        ./src/client/include/CellCounter.h ./src/client/src/Menu.cpp ./src/client/include/Menu.h ./src/client/src/AIPlayer.cpp
        ./src/client/include/AIPlayer.h ./src/client/tests/gtest_main.cpp ./src/client/tests/test_BasicLogic.cpp
        ./src/client/tests/test_AIPlayer.cpp ./src/client/tests/test_Board.cpp src/client/include/SubMenu.h
        ./src/server/include/GameCollection.h ./src/server/include/GameHolder.h ./src/server/include/CloseCommand.h
        ./src/server/include/ServerFlow.h ./src/server/include/Task.h ./src/server/src/ThreadPool.cpp ./src/server/include/ThreadPool.h)
add_executable(ReversiTest ${SOURCE_FILES_TEST} ${SOURCE_FILES})
target_link_libraries(ReversiTest gtest gtest_main)

set(SERVER_SRC_FILES ./src/server/src/Server.cpp ./src/server/include/Server.h ./src/server/src/CommandsManager.cpp
        ./src/server/src/JoinCommand.cpp ./src/server/src/PrintListCommand.cpp ./src/server/src/StartCommand.cpp
        ./src/server/include/StartCommand.h ./src/server/include/PrintListCommand.h ./src/server/include/JoinCommand.h
        ./src/server/include/CommandsManager.h ./src/server/include/Command.h ./src/server/src/GameCollection.cpp
        ./src/server/src/GameHolder.cpp ./src/server/src/CloseCommand.cpp ./src/server/src/ServerFlow.cpp
        ./src/server/include/GameCollection.h ./src/server/include/GameHolder.h ./src/server/include/CloseCommand.h
        ./src/server/include/ServerFlow.h ./src/server/include/Task.h ./src/server/src/ThreadPool.cpp ./src/server/include/ThreadPool.h)
add_executable(server ${SERVER_SRC_FILES} ./src/server/src/main.cpp)