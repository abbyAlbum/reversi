//
// Created by abby on 24/12/17.
//

#ifndef EX1_COMMANDSMANAGER_H
#define EX1_COMMANDSMANAGER_H

#include <map>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command,
                        vector<string> args);
private:
    map<string, Command *> commandsMap;
};

#endif //EX1_COMMANDSMANAGER_H
