//
// Created by abby on 24/12/17.
//

#ifndef EX1_COMMAND_H
#define EX1_COMMAND_H

#include <vector>
#include <string>
using namespace std;

class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};


#endif //EX1_COMMAND_H
