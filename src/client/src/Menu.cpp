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
    boardSize_ = DEFAULT_SIZE;
}

/**
 * runs the menu.
 * @return 1, 2 or 3 to know the
 * player type to play against.
 */
int Menu::runMenu() {
    //need to check valid input
    int oppFlag;
    cout << "Welcome to Reversi!" << endl << endl;
    cout << "Who do you want to play against?" << endl;
    cout << "1) A human player." << endl;
    cout << "2) An AI player" << endl;
    cout << "3) A player online" << endl;
    do {
        cin >> oppFlag;
    } while (oppFlag != 1 && oppFlag != 2 && oppFlag != 3);
    if (oppFlag == 3)
        return oppFlag;
    cout << "Pick your color: for black pick X." << endl;
    cout << "\t\t for white pick O." << endl;
    do {
        cin >> symbol_;
    } while (symbol_ != 'X' && symbol_ != 'O');
    delete player1_;
    player1_ = new HumanPlayer(symbol_);
    if (symbol_ == 'X') symbol_ = 'O';
    else symbol_ = 'X';

    return oppFlag;
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

/**
 * d'tor for Menu.
 */
Menu::~Menu() {
    delete player1_;
}