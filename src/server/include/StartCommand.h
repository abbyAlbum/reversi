//
// Created by abby on 24/12/17.
//

#ifndef EX1_START_H
#define EX1_START_H

#include <iostream>


using namespace std;
#include "Command.h"
#include "GameCollection.h"

using namespace std;

class StartCommand : public Command{
private:
    GameCollection *gc;

public:
    StartCommand();
    void execute(void *args);
    //~Command() {}
};

#endif //EX1_START_H
