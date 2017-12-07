//
// Created by eyal moskowitz 314074303 on 10/11/17.
//

#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H
#define BLACK 1
#define WHITE 2

#include <iostream>
#include "Player.h"
#include <limits>

using namespace std;

class HumanPlayer : public Player {
private:
    char symbol_;
public:
    HumanPlayer(char symbol);
    HumanPlayer(int color);
    Point makeMove(vector<Point> &moves);
    char getSymbol() const;
    void playerMove(vector<Point> &moves);
    void printOptions(vector<Point> &moves);
    Point getValidInput();
    ~HumanPlayer() {}
};


#endif //EX1_HUMANPLAYER_H
