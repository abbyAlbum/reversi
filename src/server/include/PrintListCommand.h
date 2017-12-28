//
// Created by abby on 24/12/17.
//

#ifndef EX1_PRINTLISTCOMMAND_H
#define EX1_PRINTLISTCOMMAND_H

#include <iostream>
#include <vector>
#include "Command.h"
#include "GameCollection.h"


using namespace std;

class PrintListCommand : public Command{
private:
    GameCollection *gc;
public:
    PrintListCommand();
    void execute(void *args);
};


#endif //EX1_PRINTLISTCOMMAND_H
