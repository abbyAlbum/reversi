//
// Created by abby on 24/12/17.
//

#include "../include/Command.h"
#include "../include/PrintListCommand.h"




void PrintListCommand:: execute(vector<string> args) {
        for (int i = 0; i < args.size(); i++) {
            cout << args[i] << " ";
        }
        cout << endl;
}


