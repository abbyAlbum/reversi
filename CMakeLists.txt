cmake_minimum_required(VERSION 3.8)
project(ex1)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Board.h Board.cpp Point.cpp Point.h Cell.cpp Cell.h GameLogic.h BasicLogic.cpp BasicLogic.h Player.h HumanPlayer.cpp HumanPlayer.h GameFlow.cpp GameFlow.h CellCounter.cpp CellCounter.h Menu.cpp Menu.h AIPlayer.cpp AIPlayer.h)
add_executable(ex1 ${SOURCE_FILES})