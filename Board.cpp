//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>

#include "Board.h"

using namespace std;

/**
 * constructor for Board
 * @param size of board
 */
Board::Board(int size) {
    bSize = size;
    board_ = new Cell*[bSize];
    Point *p;
    for (int i = 0;i < bSize;i++) {
        board_[i] = new Cell[bSize];
        for (int j = 0;j < bSize;j++) {
            p = new Point(i, j);
            board_[i][j].setValue(' ');
            board_[i][j].setPlace(p);
            delete p;
        }
    }
    board_[(bSize / 2) - 1][(bSize / 2) - 1].setValue('O');
    board_[bSize / 2][bSize / 2].setValue('O');
    board_[(bSize / 2) - 1][bSize / 2].setValue('X');
    board_[bSize / 2][(bSize / 2) - 1].setValue('X');
}

/**
 * prints the board
 */
void Board::print() {
    int printShort = (3 * bSize) + bSize + 2;
    cout << " |";
    for (int i = 0;i < bSize;i++) {
        cout << " " << i + 1 << " |";
    }
    cout << endl;
    cout << string(printShort, '-') << endl;
    for (int i = 0;i < bSize;i++) {
        cout << i + 1 << "|";
        for (int j = 0;j < bSize;j++) {
            cout << " " << board_[i][j].getValue() << " |";
        }
        cout << endl << string(printShort, '-') << endl;
    }
}

/**
 * gets the board's size
 * @return size
 */
int Board::getSize() const { return bSize; }

/**
 * gets the status of a point
 * @param p point
 * @return status
 */
char Board::getStatus(Point p) const {
    board_[p.getX()][p.getY()].getValue();
}

/**
 * puts the choice on screen and flips accordingly
 * @param p point
 * @param curr player
 * @param opp player
 */
void Board::putChoice(Point &p, Player &curr, Player &opp) {
    board_[p.getX()][p.getY()].setValue(curr.getSymbol());
    flipSides(p.getX(), p.getY(), curr, opp);
    flipDiag(p.getX(), p.getY(), curr, opp);
}

/**
 * flips the sides
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 */
void Board::flipSides(int i, int j, Player &curr, Player &opp) {
    bool flag = false;
    bool &f = flag;
    if (i != bSize - 1) {
        flipDown(i + 1, j, curr, opp, f);
        f = false;
    }
    if (i != 0) {
        flipUp(i - 1, j, curr, opp, f);
        f = false;
    }
    if (j != 0) {
        flipLeft(i, j - 1, curr, opp, f);
        f = false;
    }
    if (j != bSize - 1) {
        flipRight(i, j + 1, curr, opp, f);
        f = false;
    }
}

/**
 * flips diagonals
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 */
void Board::flipDiag(int i, int j, Player &curr, Player &opp) {
    bool flag = false;
    bool &f = flag;
    if (i != 0 && j != 0) {
        flipUpL(i - 1, j - 1, curr, opp, f);
        f = false;
    }
    if (i != 0 && j != bSize - 1) {
        flipUpR(i - 1, j + 1, curr, opp, f);
        f = false;
    }
    if (i != bSize - 1 && j != 0) {
        flipDownL(i + 1, j - 1, curr, opp, f);
        f = false;
    }
    if (i != bSize - 1 && j != bSize - 1) {
        flipDownR(i + 1, j + 1, curr, opp, f);
        f = false;
    }
}

/**
 * flips down
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipDown(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipDown(i - 1, j, curr, opp, flag);
        }
    }
    else if (i != bSize - 1) {
        if (!flag)
            flipDown(i + 1, j, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipDown(i - 1, j, curr, opp, flag);
        }
    }
}

/**
 * flips up
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipUp(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipUp(i + 1, j, curr, opp, flag);
        }
    }
    else if (i != 0) {
        if (!flag)
            flipUp(i - 1, j, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipUp(i + 1, j, curr, opp, flag);
        }
    }
}

/**
 * flips left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipLeft(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipLeft(i, j + 1, curr, opp, flag);
        }
    }
    else if (j != 0) {
        if (!flag)
            flipLeft(i, j - 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipLeft(i, j + 1, curr, opp, flag);
        }
    }
}

/**
 * flips right
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipRight(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipRight(i, j - 1, curr, opp, flag);
        }
    }
    else if (j != bSize - 1) {
        if (!flag)
            flipRight(i, j + 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipRight(i, j - 1, curr, opp, flag);
        }
    }
}

/**
 * flips up left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipUpL(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipUpL(i + 1, j + 1, curr, opp, flag);
        }
    }
    else if (i != 0 && j != 0) {
        if (!flag)
            flipUpL(i - 1, j - 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipUpL(i + 1, j + 1, curr, opp, flag);
        }
    }
}

/**
 * flips up right
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipUpR(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipUpR(i + 1, j - 1, curr, opp, flag);
        }
    }
    else if (i != 0 && j != bSize - 1) {
        if (!flag)
            flipUpR(i - 1, j + 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipUpR(i + 1, j - 1, curr, opp, flag);
        }
    }
}

/**
 * flips down left
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipDownL(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipDownL(i - 1, j + 1, curr, opp, flag);
        }
    }
    else if (i != bSize - 1 && j != 0) {
        if (!flag)
            flipDownL(i + 1, j - 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipDownL(i - 1, j + 1, curr, opp, flag);
        }
    }
}

/**
 * flips down right
 * @param i row
 * @param j col
 * @param curr player
 * @param opp player
 * @param flag indicates that we got to another tile of the curr
 */
void Board::flipDownR(int i, int j, Player &curr, Player &opp, bool &flag) {
    if (board_[i][j].getValue() == ' ')
        return;
    if (board_[i][j].getValue() == curr.getSymbol()) {
        if (!flag) {
            flag = true;
            flipDownR(i - 1, j - 1, curr, opp, flag);
        }
    }
    else if (i != bSize - 1 && j != bSize - 1) {
        if (!flag)
            flipDownR(i + 1, j + 1, curr, opp, flag);
        else {
            board_[i][j].setValue(curr.getSymbol());
            flipDownR(i - 1, j - 1, curr, opp, flag);
            }
    }
}

/**
 * deconstructor for Board
 */
Board::~Board() {
    for (int i = 0;i < bSize;i++) {
        delete[] board_[i];
    }
    delete board_;
}















