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
    void executeCommand(string command, void *args);
    static CommandsManager * getInstance();
private:
    map<string, Command *> commandsMap;
    static CommandsManager *instance;
};

#endif //EX1_COMMANDSMANAGER_H
