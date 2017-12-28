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
string SubMenu::runSubMenu() {
    //need to check valid input
    int oppFlag;
    string name;
    string command;
    cout << "Choose an option" << endl;
    cout << "1) Start a new game" << endl;
    cout << "2) Join an existing game" << endl;
    cout << "3) See existing games" << endl;
    do {
        cin >> oppFlag;
    } while (oppFlag != 1 && oppFlag != 2 && oppFlag != 3);
    if(oppFlag == 1) {
        cout << "input the name of the game you want to start" << endl;
            cin >> name;
        command = "start" + name;
    }
    if(oppFlag == 2) {
        cout << "input the name of the game you want to join" << endl;
        cin >> name;
        command = "join" + name;
    }
    if(oppFlag == 3) {
        command = "list_games";
    }
    return command;
}

SubMenu::~SubMenu() {

}