//
// Created by abby on 24/12/17.
//

#ifndef EX1_JOIN_H
#define EX1_JOIN_H

#include <iostream>


using namespace std;

#include "Command.h"

using namespace std;

class JoinCommand: public Command{
private:

public:
    void execute(vector<string> args);
    //~Command() {}
};

#endif //EX1_JOIN_H
