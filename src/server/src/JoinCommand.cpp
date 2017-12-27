//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/JoinCommand.h"
#include "../include/ServerFlow.h"

/**
 * Creates the join command
 * @param gc  - the game collection
 */
JoinCommand::JoinCommand(GameCollection *gc) {
    gameCollection = gc;
}

/**
 * Player joins the game they chose from the list of possible games they can play
 * @param args - the name of the game the client wants to play
 */
void JoinCommand:: execute(vector<string> args) {
    //can join the game
    for(int i = 0; i < gameCollection->getList().size(); i++) {
        if(gameCollection->getList()[i].getName() == args[0]) {
            //if this is a game that the player can join
            if(gameCollection->getList()[i].isJoinable()) {
                gameCollection->getList()[i].setSocketPlayer2(socket);
                //sends this game to the server
                ServerFlow sf(&gameCollection->getList()[i]);
                sf.handleClient();
            }
        }
    }
}
