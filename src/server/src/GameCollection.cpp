//
// Created by abby on 26/12/17.
//

#include "../include/GameCollection.h"
#include "../include/GameHolder.h"

/**
 * C'tor for GameCollection
 */
GameCollection:: GameCollection() {}

/**
 * Adds a game to the list
 * @param gh - the gameholder
 */
void GameCollection:: add(GameHolder gh) {
    log.push_back(gh);
}

/**
 * Gets the list
 * @return - the list of games
 */
vector<GameHolder> GameCollection::getList() {
    return log;
}

/**
 * Removes a game from the list
 * @param name - the name of the game
 */
void GameCollection::remove(string name) {
    for(int i = 0; i < log.size(); i++) {
        if(name == log[i].getName()) {
            log.erase(log.begin() + i);
            break;
        }
    }
}

void GameCollection::joinGame(int i, int socket) {
    log[i].setSocketPlayer2(socket);
    log[i].setJoinable();
}

// Null, because instance will be initialized on demand.
GameCollection *GameCollection::instance = 0;

GameCollection* GameCollection::getInstance() {
    if (instance == 0) instance = new GameCollection();
    return instance;
}