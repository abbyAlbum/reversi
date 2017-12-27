//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/StartCommand.h"

/**
 * Creat the start command
 * @param s  - the socket
 * @param gameCollection  - the game collection
 */
StartCommand::StartCommand(int s, GameCollection *gameCollection) {
    socket = s;
    gc = gameCollection;
}

/**
 * Start own game- add to the list of games
 * @param args - the game you want to start
 */
void StartCommand:: execute(vector<string> args) {
//    string name;
//    string start;
//    cout << "choose a name for your game" << endl;
//    cout << "input 'start' followed by the name of your game" << endl;
//    do {
//        cin >> start, name;
//    } while (start.compare("start") != 0);
    GameHolder gh = GameHolder(args[0], socket);
    for(int i = 0; i < gc->getList().size(); i++) {
        //if already appears in list
        if (gh.getName() == gc->getList()[i].getName()) {
            //TODO write to client -1
            return;
        }
    }
    gc->add(gh);
}


