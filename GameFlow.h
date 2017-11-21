//
// Created by eyal moskowitz 314074303 on 10/11/17.
//

#ifndef EX1_GAMEFLOW_H
#define EX1_GAMEFLOW_H


#include "Board.h"
#include "GameLogic.h"
#include "BasicLogic.h"
#include "HumanPlayer.h"
#include "CellCounter.h"

class GameFlow {
private:
    char currentPlayer_;
    int *turnsLeft_;
    Board *board_;
    GameLogic *logic_;
public:
    GameFlow(int boardSize);
    void playOneTurn(Player &curr, Player &opp, CellCounter &cc);
    void run(Player &player, int whichPlayer, char symbol);
    ~GameFlow();
};


#endif //EX1_GAMEFLOW_H
