//
// Created by abby on 24/12/17.
//

#include <cstring>
#include "../include/Command.h"
#include "../include/PrintListCommand.h"
#include "../include/Server.h"

/**
 * Creates the print list command
 * @param gc - the list of games - game collection
 */
PrintListCommand:: PrintListCommand() {
    gc = GameCollection::getInstance();
}

/**
 * Prints the lists of games
 * @param args - the command
 */
void PrintListCommand:: execute(void *args) {
    Args *arg = (Args *)args;
    string s = "";
    //print the list of games the player can join
    for(int i = 0; i <gc->getList().size(); i++) {
        if(gc->getList()[i].isJoinable()) {
            s += gc->getList()[i].getName() + "\n";
        }
    }
    s += "\n";
    char *buffer = new char[s.length() + 1];
    strcpy(buffer, s.c_str());
    Server::writeSocket(arg->socket, buffer);
    delete[] buffer;
}


