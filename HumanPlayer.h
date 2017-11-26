//
// Created by eyal moskowitz 314074303 on 10/11/17.
//

#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H

#include <iostream>
#include "Player.h"
#include <limits>

using namespace std;

class HumanPlayer : public Player {
private:
    char symbol_;
public:
    HumanPlayer(char symbol);
    Point makeMove(vector<Point> &moves);
    char getSymbol() const;
    void playerMove(vector<Point> &moves);
    void printOptions(vector<Point> &moves);
    Point getValidInput();
    ~HumanPlayer() {}
};


#endif //EX1_HUMANPLAYER_H
