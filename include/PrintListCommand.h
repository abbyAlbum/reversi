//
// Created by abby on 24/12/17.
//

#ifndef EX1_PRINTLISTCOMMAND_H
#define EX1_PRINTLISTCOMMAND_H

#include <iostream>
#include <vector>
#include "Command.h"


using namespace std;

class PrintListCommand : public Command{
private:

public:
    void execute(vector<string> args);
};


#endif //EX1_PRINTLISTCOMMAND_H
