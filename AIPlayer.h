//
// Created by abby on 21/11/17.
//

#ifndef EX1_AIPLAYER_H
#define EX1_AIPLAYER_H
#include <iostream>
#include "Player.h"
#include "Board.h"
#include "GameLogic.h"
#include "CellCounter.h"

class AIPlayer : public Player{
public:
    AIPlayer(char symbol, Board *board, Player *opp);
    Point makeMove(vector<Point> &moves);
    int makeHumanPLayerMove(Board copyBoard, Point move);

private:
    char symbol_;
    Board *board_;
    Player *opp_;
};


#endif //EX1_AIPLAYER_H
