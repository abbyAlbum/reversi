//
// Created by abby on 26/12/17.
//

#include "../include/GameCollection.h"
#include "../include/CloseCommand.h"

pthread_mutex_t remove_mutex;
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
    GameHolder *arg = (GameHolder *) args;
    pthread_mutex_lock(&remove_mutex);
    gc->remove(arg->getName());
    pthread_mutex_unlock(&remove_mutex);
}
