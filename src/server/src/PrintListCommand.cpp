//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/PrintListCommand.h"

/**
 * Creates the print list command
 * @param gc - the list of games - game collection
 */
PrintListCommand:: PrintListCommand(GameCollection *gc) {
    gameCollection = gc;
}

/**
 * Prints the lists of games
 * @param args - the command
 */
void PrintListCommand:: execute(vector<string> args) {
    //print the list of games the player can join
    for(int i = 0; i <gameCollection->getList().size(); i++) {
        if(gameCollection->getList()[i].isJoinable()) {
            cout << gameCollection->getList()[i].getName() << endl;
        }
    }
    cout << endl;
}


