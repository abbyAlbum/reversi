//
// Created by abby on 26/12/17.
//

#include "../include/GameCollection.h"
#include "../include/CloseCommand.h"

/**
 * Creates the close command
 * @param gc - the game collection
 */
CloseCommand:: CloseCommand(GameCollection *gc) {
    gameCollection = gc;
}

/**
 * Removes this game from the list, and the thread
 * @param args  - this game
 */
void CloseCommand:: execute(vector<string> args) {
    gameCollection->remove(args[0]);
   //TODO CLOSE THREAD

}
