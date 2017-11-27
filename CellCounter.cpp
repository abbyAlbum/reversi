//
// Created by eyal moskowitz 314074303 on 13/11/17.
//

#include "CellCounter.h"

/**
 * constructor for CellCounter
 * @param board
 */
CellCounter::CellCounter(Board *board) {
    board_ = board;
    xCounter_ = 0;
    oCounter_ = 0;
    spaceCounter_ = 0;
}

/**
 * counts the num of cells of each type in each turn
 */
void CellCounter::count() {
    Point p;
    xCounter_ = 0;
    oCounter_ = 0;
    spaceCounter_ = 0;
    for (int i = 0; i < board_->getSize(); ++i) {
        for (int j = 0; j < board_->getSize(); ++j) {
            p = Point(i, j);
            if (board_->getStatus(p) == 'X') xCounter_++;
            if (board_->getStatus(p) == 'O') oCounter_++;
            if (board_->getStatus(p) == ' ') spaceCounter_++;
        }
    }
}

/**
 * gets the num of 2nd player's occupied cells
 * @return num of cells
 */
int CellCounter::getOCounter() const { return oCounter_; }

/**
 * gets the num of unoccupied
 * @return num of cells
 */
int CellCounter::getSpaceCounter() const { return spaceCounter_; }

/**
 * gets the num of 1st player's occupied cells
 * @return num of cells
 */
int CellCounter::getXCounter() const { return xCounter_; }