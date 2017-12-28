//
// Created by eyal moskowitz 314074303 on 02/11/17.
//


#include "../include/Cell.h"

/**
 * constructor for Cell
 */
Cell::Cell() {}

/**
 * constructor for Cell
 * @param p point
 * @param val value
 */
Cell::Cell(Point *p, char val) {
    place_ = p;
    val_ = val;
}

/**
 * gets the cell's value
 * @return value
 */
char Cell::getValue() const { return val_; }

/**
 * sets the cell's value
 * @param val value
 */
void Cell::setValue(char val) { val_ = val; }

/**
 * sets the place of the cell
 * @param p point
 */
void Cell::setPlace(Point *p) {
    place_ = new Point(p->getX(), p->getY());
}

Cell::~Cell() { delete place_;}