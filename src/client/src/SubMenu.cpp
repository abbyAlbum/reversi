//
// Created by abby on 24/12/17.
//

#include "../include/HumanPlayer.h"
#include "../include/SubMenu.h"

/**
 * constructor for menu.
 */
SubMenu::SubMenu() {

}

/**
 * runs the submenu.
 * @return 1, 2 or 3 to know the
 * the choice of the player
 */
int SubMenu::runSubMenu() {
    //need to check valid input
    int oppFlag;
    cout << "Choose an option" << endl;
    cout << "1) Start a new game" << endl;
    cout << "2) Join an existing game" << endl;
    cout << "3) See existing games" << endl;
    do {
        cin >> oppFlag;
    } while (oppFlag != 1 && oppFlag != 2 && oppFlag != 3);
    return oppFlag;
}

SubMenu::~SubMenu() {

}