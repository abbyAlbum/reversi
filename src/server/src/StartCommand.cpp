//
// Created by abby on 24/12/17.
//

#include <cstring>
#include "../include/Command.h"
#include "../include/StartCommand.h"
#include "../include/Server.h"

pthread_mutex_t add_mutex;
/**
 * Creat the start command
 * @param s  - the socket
 * @param gameCollection  - the game collection
 */
StartCommand::StartCommand() {
    gc = GameCollection::getInstance();
}

/**
 * Start own game- add to the list of games
 * @param args - the game you want to start
 */
void StartCommand:: execute(void *args) {

    Args *arg = (Args *)args;
    pthread_mutex_lock(&add_mutex);
    GameHolder gh = GameHolder(arg->name, arg->socket);
    for(int i = 0; i < gc->getList().size(); i++) {
        //if already appears in list
        if (gh.getName() == gc->getList()[i].getName()) {
            Server::writeSocket(arg->socket, "-1");
            return;
        }
    }
    gc->add(gh);
    pthread_mutex_unlock(&add_mutex);
    Server::writeSocket(arg->socket, "waiting for other player to join...");
}