//
// Created by eyal moskowitz 314074303 on 26/10/17.
//

#ifndef EX1_BOARD_H
#define EX1_BOARD_H

#include "Cell.h"
#include "Player.h"

class Board {
private:
    Cell **board_;
    int bSize;
public:
    //Board();
    Board(int size);
    Board(Board *copyBoard);
    void print();
    int getSize() const;
    char getStatus(Point p) const;
    void setStatus(char symbol, Point p);
    void putChoice(Point &p, Player &curr, Player &opp);
    void flipSides(int i, int j, Player &curr, Player &opp);
    void flipDiag(int i, int j, Player &curr, Player &opp);
    void flipDown(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipUp(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipLeft(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipRight(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipUpL(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipUpR(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipDownL(int i, int j, Player &curr, Player &opp, bool &flag);
    void flipDownR(int i, int j, Player &curr, Player &opp, bool &flag);
    ~Board();
};
#endif //EX1_BOARD_H
