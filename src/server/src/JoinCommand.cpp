//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/JoinCommand.h"
#include "../include/ServerFlow.h"
#include "../include/Server.h"

/**
 * Creates the join command
 * @param gc  - the game collection
 */
JoinCommand::JoinCommand() {
    gc = GameCollection::getInstance();
}

/**
 * Player joins the game they chose from the list of possible games they can play
 * @param args - the name of the game the client wants to play
 */
void JoinCommand::execute(void *args) {
    Args *arg = (Args *)args;
    //can join the game
    for(int i = 0; i < gc->getList().size(); i++) {
        if(gc->getList()[i].getName() == arg->name) {
            //if this is a game that the player can join
            if(gc->getList()[i].isJoinable()) {
                gc->joinGame(i, arg->socket);
                //sends this game to the server
                GameHolder gh = gc->getList()[i];
                string name = gc->getList()[i].getName();
                //gh->setName(name);
                ServerFlow sf(&gh);
                Server::writeSocket(arg->socket, "waiting for other player's move");
                sf.handleClient();
                return;
            }
        }
    }
    Server::writeSocket(arg->socket, "-1");
}
