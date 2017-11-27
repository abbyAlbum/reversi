//
// Created by eyal moskowitz 314074303 on 05/11/17.
//

#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include "Point.h"
#include <vector>

using namespace std;

class Player {
public:
    virtual Point makeMove(vector<Point> &possibleMoves) = 0;
    virtual char getSymbol() const = 0;
};

#endif //EX1_PLAYER_H
