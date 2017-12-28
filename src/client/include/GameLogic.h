//
// Created by eyal moskowitz 314074303 on 05/11/17.
//

#ifndef EX1_GAMELOGIC_H
#define EX1_GAMELOGIC_H

#include <vector>
#include "Point.h"
#include "Board.h"
#include "Player.h"

using namespace std;

class GameLogic {
public:
    virtual vector<Point> getPossibleMoves(Player &curr, Player &opp) = 0;
};

#endif //EX1_GAMELOGIC_H
