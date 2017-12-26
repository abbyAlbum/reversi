//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/JoinCommand.h"


void JoinCommand:: execute(vector<string> args) {
    string name;
    string join;
    cout << "choose a game from the lst" << endl;
    cout << "input 'join' followed by the name of your game" << endl;
    do {
        cin >> join, name;
    } while (join != "join" && );

    for(int i = 0; i < args.size(); i++) {
        if(name == args[i]) {
           // return args[i];
        }
        else {
            cout << "Name not in list, try again" << endl;
            cin >> name;
        }
    }
}
