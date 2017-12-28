//
// Created by abby on 26/12/17.
//

#include "../include/GameCollection.h"
#include "../include/CloseCommand.h"

/**
 * Creates the close command
 * @param gc - the game collection
 */
CloseCommand:: CloseCommand() {
    gc = GameCollection::getInstance();
}

/**
 * Removes this game from the list, and the thread
 * @param args  - this game
 */
void CloseCommand:: execute(void *args) {
    Args *arg = (Args *)args;
    gc->remove(arg->name);
   //TODO CLOSE THREAD

}
