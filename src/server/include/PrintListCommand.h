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
    int socket;
    GameCollection *gameCollection;
public:
    PrintListCommand(GameCollection *gameCollection1);
    void execute(vector<string> args);
};


#endif //EX1_PRINTLISTCOMMAND_H
