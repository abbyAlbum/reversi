//
// Created by eyal moskowitz 314074303 on 05/11/17.
//

#ifndef EX1_BASICLOGIC_H
#define EX1_BASICLOGIC_H

#include <algorithm>
#include "GameLogic.h"

class BasicLogic : public GameLogic {
private:
    Board *board_;
public:
    BasicLogic(Board *board);
    vector<Point> getPossibleMoves(Player &curr, Player &opp);
    Point checkUp(int i, int j, Player &curr, Player &opp);
    Point checkDown(int i, int j, Player &curr, Player &opp);
    Point checkLeft(int i, int j, Player &curr, Player &opp);
    Point checkRight(int i, int j, Player &curr, Player &opp);
    Point checkUpL(int i, int j, Player &curr, Player &opp);
    Point checkUpR(int i, int j, Player &curr, Player &opp);
    Point checkDownR(int i, int j, Player &curr, Player &opp);
    Point checkDownL(int i, int j, Player &curr, Player &opp);
    vector<Point> checkSides(int i, int j, Player &curr, Player &opp);
    vector<Point> checkDiag(int i, int j, Player &curr, Player &opp);
    vector<Point> checkAround(int i, int j, Player &curr, Player &opp);
    void printOptions(vector<Point> &moves);
    void addIfValid(vector<Point> *moves, Point *p);
};


#endif //EX1_BASICLOGIC_H
