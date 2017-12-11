//
// Created by eyal on 21/11/17.
//

#ifndef EX1_MENU_H
#define EX1_MENU_H
#define DEFAULT_SIZE 8

#include <iostream>
#include "Player.h"

using namespace std;

class Menu {
private:
    char symbol_;
    Player* player1_;
    int boardSize_;
public:
    Menu();
    int runMenu();
    int getBoardSize() const;
    Player& getPlayer() const;
    char getSymbol() const;
    ~Menu();
};


#endif //EX1_MENU_H
