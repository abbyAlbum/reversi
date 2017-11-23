//
// Created by eyal moskowitz 314074303 on 05/11/17.
//

#include <iostream>
#include "BasicLogic.h"

/**
 * constructor for BasicLogic
 * @param board
 */
BasicLogic::BasicLogic(Board *board) {
    board_ = board;
}

/**
 * returns the player's possible moves
 * @param curr current player
 * @param opp opponent
 * @return possible moves
 */
vector<Point> BasicLogic::getPossibleMoves(Player &curr, Player &opp) {
    vector<Point> possibleMoves;
    for (int i = 0; i < board_->getSize(); ++i) {
        for (int j = 0; j < board_->getSize(); ++j) {
            if (board_->getStatus(Point(i, j)) == curr.getSymbol()) {
                vector<Point> moves = checkAround(i, j, curr, opp);
                possibleMoves.insert(possibleMoves.end(), moves.begin(), moves.end());
            }
        }
    }
    vector<Point> &moves = possibleMoves;
    sort(possibleMoves.begin(), possibleMoves.end());
    possibleMoves.erase(unique(possibleMoves.begin(), possibleMoves.end()), possibleMoves.end());
    //printOptions(moves);
    return possibleMoves;
}

/**
 * returns the possible moves from a specific point.
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return point's possible moves
 */
vector<Point> BasicLogic::checkAround(int i, int j, Player &curr, Player &opp) {
    vector<Point> moves, sides, diag;
    sides = checkSides(i, j, curr, opp);
    moves.insert(moves.end(), sides.begin(), sides.end());
    diag = checkDiag(i, j, curr, opp);
    moves.insert(moves.end(), diag.begin(), diag.end());
    return moves;
}

/**
 * adds point to vector if valid
 * @param moves vector
 * @param p potential move to add
 */
void BasicLogic::addIfValid(vector<Point> *moves, Point *p) {
    if (p->getX() != -1) moves->push_back(*p);
}

/**
 * checks up
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkUp(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    if (i != 0)
        checkUp(i - 1, j, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks down
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkDown(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    if (i != board_->getSize() - 1)
        checkDown(i + 1, j, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkLeft(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    if (j != 0)
        checkLeft(i, j - 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks rigt
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkRight(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    if (j != board_->getSize() - 1)
        checkRight(i, j + 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks up left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkUpL(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    if (j != 0 && i != 0)
        checkUpL(i - 1, j - 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks up right
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkUpR(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    else if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    else if (j != board_->getSize() - 1 && i != 0)
        checkUpR(i - 1, j + 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks down right
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkDownR(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    else if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    else if (j != board_->getSize() - 1 && i != board_->getSize() - 1)
        checkDownR(i + 1, j + 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks down left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return potential move
 */
Point BasicLogic::checkDownL(int i, int j, Player &curr, Player &opp) {
    if (board_->getStatus(Point(i, j)) == curr.getSymbol()) return Point(-1, -1);
    else if (board_->getStatus(Point(i, j)) == ' ') return Point(i + 1, j + 1);
    else if (j != 0 && i != board_->getSize() - 1)
        checkDownL(i + 1, j - 1, curr, opp);
    else return Point(-1, -1);
}

/**
 * checks the sides
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return vector of possible moves
 */
vector<Point> BasicLogic::checkSides(int i, int j, Player &curr, Player &opp) {
    vector<Point> moves;
    Point p;
    if (i != 0 && board_->getStatus(Point(i - 1, j)) == opp.getSymbol()) {
        p = checkUp(i - 1, j, curr, opp);
        addIfValid(&moves, &p);
    }
    if (i != board_->getSize() - 1 && board_->getStatus(Point(i + 1, j)) == opp.getSymbol()) {
        p = checkDown(i + 1, j, curr, opp);
        addIfValid(&moves, &p);
    }
    if (j != 0 && board_->getStatus(Point(i, j - 1)) == opp.getSymbol()) {
        p = checkLeft(i, j - 1, curr, opp);
        addIfValid(&moves, &p);
    }
    if (j != board_->getSize() - 1 && board_->getStatus(Point(i, j + 1)) == opp.getSymbol()) {
        p = checkRight(i, j + 1, curr, opp);
        addIfValid(&moves, &p);
    }
    return moves;
}

/**
 * checks the diagonals
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @return vector of possible moves
 */
vector<Point> BasicLogic::checkDiag(int i, int j, Player &curr, Player &opp) {
    vector<Point> moves;
    Point p;
    if (i != 0 && j != 0 && board_->getStatus(Point(i - 1, j - 1)) == opp.getSymbol()) {
        p = checkUpL(i - 1, j - 1, curr, opp);
        addIfValid(&moves, &p);
    }
    if (i != 0 && j != board_->getSize() - 1 && board_->getStatus(Point(i - 1, j + 1)) == opp.getSymbol()) {
        p = checkUpR(i - 1, j + 1, curr, opp);
        addIfValid(&moves, &p);
    }
    if (i != board_->getSize() - 1 && j != board_->getSize() - 1
        && board_->getStatus(Point(i + 1, j + 1)) == opp.getSymbol()) {
        p = checkDownR(i + 1, j + 1, curr, opp);
        addIfValid(&moves, &p);
    }
    if (i != board_->getSize() - 1 && j != 0 && board_->getStatus(Point(i + 1, j - 1)) == opp.getSymbol()) {
        p = checkDownL(i + 1, j - 1, curr, opp);
        addIfValid(&moves, &p);
    }
    return moves;
}