//
// Created by eyal moskowitz 314074303 on 21/11/17.
//

#include "../include/Menu.h"
#include "../include/HumanPlayer.h"

/**
 * constructor for menu.
 */
Menu::Menu() {
    symbol_ = 'X';
    player1_ = new HumanPlayer(symbol_);
}

/**
 * runs the menu.
 * @return 0 if the player doesn't want to play and 1 or 2 to know the
 * player type to play against.
 */
int Menu::runMenu() {
    //need to check valid input
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

/**
 * gets the size of the board the player chose.
 * @return the board size
 */
int Menu::getBoardSize() const { return boardSize_; }

/**
 * gets player 1.
 * @return player 1
 */
Player& Menu::getPlayer() const { return *player1_; }

/**
 * gets the symbol for the other player.
 * @return player 2's symbol
 */
char Menu::getSymbol() const { return symbol_; }