//
// Created by abby on 26/12/17.
//

#include <unistd.h>
#include "../include/GameCollection.h"
#include "../include/CloseCommand.h"
#include "../include/Server.h"

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
    for (int i = 0; i < gc->getList().size(); ++i) {
        cout << gc->getList()[i].getName() << endl;
    }
    GameHolder *arg = (GameHolder *) args;
    gc->remove(arg->getName());
    for (int i = 0; i < gc->getList().size(); ++i) {
        cout << gc->getList()[i].getName() << endl;
    }
    close(arg->getSocketPLayer1());
    close(arg->getSocketPlayer2());
}
