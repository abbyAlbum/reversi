//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/StartCommand.h"



void StartCommand:: execute(vector<string> args) {
    string name;
    cout << "choose a name for your game" << endl;
    cin >> name;
    for(int i = 0; i < args.size(); i++) {
        if(name == args[i]) {
            //return 1 to client
        }
    }
    args.push_back(name);
}


