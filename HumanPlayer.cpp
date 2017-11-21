//
// Created by eyal moskowitz 314074303 on 10/11/17.
//

#include "HumanPlayer.h"

/**
 * constructor for HumanPlayer.
 * @param symbol
 */
HumanPlayer::HumanPlayer(char symbol) {
    symbol_ = symbol;
}

/**
 * lets the player to make a move
 * @param moves possible moves for the player
 * @return the player's choice
 */
Point HumanPlayer::makeMove(vector<Point> &moves) {
    if (moves.empty()) {
        cout << "You have no possible moves, other player's turn." << endl;
        return Point(-1, -1);
    }
    Point p;
    cout << "Please enter row and column (separated with space):" << endl;
    while (true) {
        p = getValidInput();
        bool isInMoves = false;
        for (int i = 0; i < moves.size(); ++i) {
            if (p == moves[i]) {
                isInMoves = true;
                break;
            } else isInMoves = false;
        }
        if (isInMoves) break;
        else {
            cout << "Your choice is illegal, please try again:" << endl;
        }
    }
    return p;
}

/**
 * makes sure that we get only numbers
 * @return the player's choice
 */
Point HumanPlayer::getValidInput() {
    int row, col;
    while (true) {
        cin >> row >> col;
        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return Point(row, col);
        }

        // user didn't input row and column
        cout << "Please enter numbers only." << endl;
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * gets the player's symbol
 * @return symbol
 */
char HumanPlayer::getSymbol() const { return symbol_; }