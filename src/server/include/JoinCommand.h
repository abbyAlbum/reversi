//
// Created by abby on 24/12/17.
//

#ifndef EX1_JOIN_H
#define EX1_JOIN_H

#include <iostream>


using namespace std;

#include "Command.h"
#include "GameCollection.h"

using namespace std;

class JoinCommand: public Command{
private:
    GameCollection *gc;
public:
    JoinCommand();
    void execute(void *args);
    //~Command() {}
};

#endif //EX1_JOIN_H
