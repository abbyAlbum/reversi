//
// Created by eyal moskowitz 314074303 on 02/11/17.
//

#ifndef EX1_CELL_H
#define EX1_CELL_H

#include "Point.h"

class Cell {
private:
    char val_;
    Point *place_;
public:
    Cell();
    Cell(Point *p, char val);
    char getValue() const;
    void setValue(char val);
    void setPlace(Point *p);
    ~Cell();
};


#endif //EX1_CELL_H
