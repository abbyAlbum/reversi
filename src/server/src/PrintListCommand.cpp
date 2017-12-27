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
    for (int i = 0; i < gameCollection->getList().size(); i++) {
        cout << gameCollection->getList()[i].getName() << " ";
    }
    cout << endl;
}


