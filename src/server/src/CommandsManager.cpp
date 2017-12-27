//
// Created by abby on 24/12/17.
//

#include "../include/CommandsManager.h"
#include "../include/StartCommand.h"
#include "../include/JoinCommand.h"
#include "../include/PrintListCommand.h"
#include "../include/CloseCommand.h"

/**
 * Creates the commandManager - each command
 */
CommandsManager::CommandsManager() {
    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new PrintListCommand();
    commandsMap["join"] = new JoinCommand();
    commandsMap["close"] = new CloseCommand();
}

/**
 * Executes the command
 * @param command - the name of the command
 * @param args - the command, name of game
 */
void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj->execute(args);
}

/**
 * Deconstructor for commands
 */
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}