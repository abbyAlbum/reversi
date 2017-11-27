//
// Created by eyal moskowitz 314074303 on 13/11/17.
//

#ifndef EX1_CELLCOUNTER_H
#define EX1_CELLCOUNTER_H


#include "Board.h"

class CellCounter {
private:
    Board *board_;
    int xCounter_;
    int oCounter_;
    int spaceCounter_;
public:
    CellCounter(Board *board);
    void count();
    int getXCounter() const;
    int getOCounter() const;
    int getSpaceCounter() const;
};


#endif //EX1_CELLCOUNTER_H
