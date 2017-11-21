//
// Created by eyal moskowitz 314074303 on 21/11/17.
//

#include "Menu.h"
#include "HumanPlayer.h"

Menu::Menu() {
    symbol_ = 'X';
    player1_ = new HumanPlayer(symbol_);
}

int Menu::runMenu() {
    char play, oppFlag;
    cout << "Hello! Want to play a game of Othello?" << endl << "y) Yes"
         << endl << "n) No" << endl;
    cin >> play;
    if (play == 'n') return 0;
    cout << "Let's set up the game." << endl;
    cout << "Pick the board size: 6 or 8." << endl;
    cin >> boardSize_;
    cout << "Pick your color: for black pick X." << endl;
    cout << "\t\t\t\t for white pick O." << endl;
    cin >> symbol_;
    delete player1_;
    player1_ = new HumanPlayer(symbol_);
    if (symbol_ == 'X') symbol_ = 'O';
    else symbol_ = 'X';
    cout << "Who do you want to play against?" << endl;
    cout << "Press a to play against a human player." << endl;
    cout << "Press b to play against the computer." << endl;
    cin >> oppFlag;
    if (oppFlag == 'a') return 1;
    else return 2;
}

int Menu::getBoardSize() const { return boardSize_; }

Player& Menu::getPlayer() const { return *player1_; }

char Menu::getSymbol() const { return symbol_; }