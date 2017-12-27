//
// Created by abby on 26/12/17.
//

#include "../include/GameHolder.h"

/**
 * Creates the gameholder
 * @param s  - the name.
 * @param socket - the socket
 */
GameHolder::GameHolder(string s, int socket) {
    name = s;
    socketPlayer1 = socket;
    joinable = true;
}

/**
 * Gets the name.
 * @return the string name
 */
string GameHolder::getName() {
    return name;
}

/**
 * Gets the first socket
 * @return the first socket.
 */
int GameHolder::getSocketPLayer1() {
    return socketPlayer1;
}

/**
 * Gets the second socket
 * @return the second socket
 */
int GameHolder::getSocketPlayer2() {
    return socketPlayer2;
}

/**
 * see if can join game
 * @return true if can join, false otherwise
 */
bool GameHolder:: isJoinable() {
    return joinable;
}

/**
 * Sets the join flag - can join a game or not
 * @param flag - the flag
 */
void GameHolder::setJoinable(bool flag) {
    joinable = flag;
}

/**
 * Sets the second socket
 * @param socketPlayer2 - the second socket
 */
void GameHolder::setSocketPlayer2(int socketPlayer2) {
    GameHolder::socketPlayer2 = socketPlayer2;
}
