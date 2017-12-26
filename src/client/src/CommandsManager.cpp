//
// Created by abby on 24/12/17.
//


#include "../include/CommandsManager.h"
#include "../include/PrintListCommand.h"
#include "../include/StartCommand.h"
#include "../include/JoinCommand.h"

CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new PrintListCommand();
    commandsMap["join"] = new JoinCommand();


}

void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}