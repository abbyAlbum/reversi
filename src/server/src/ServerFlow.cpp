//
// Created by abby on 26/12/17.
//

#include "../include/ServerFlow.h"
#include "../include/GameHolder.h"
#include "Server.cpp"
#include <iostream>

/**
 * Creates the serverflow
 * @param gameHolder - gets this specific game
 */
ServerFlow::ServerFlow(GameHolder *gameHolder) {
    gh = gameHolder;
}

/**
 * Handle requests from a specific client
 * @param clientSocket - the first client socket.
 * @param clientSocket2 - the second client socket.
 */
void ServerFlow::handleClient() {
    int counter = 1;
    int num, firstSocket, secondSocket;
    char buffer[100] = {0};
    strcpy(buffer, "black");
    char buffer2[100] = {0};
    strcpy(buffer, "white");
    //tell the clients which player they are, depending on who joined first
    Server::writeSocket(gh->getSocketPLayer1(), buffer);
    Server::writeSocket(gh->getSocketPLayer1(), buffer2);
    firstSocket = gh->getSocketPLayer1();
    secondSocket = gh->getSocketPlayer2();
    while (true) {
        if (counter % 2 == 1)
            num = passMessage(firstSocket, secondSocket);
        else
            num = passMessage(secondSocket, firstSocket);
        counter++;
        if(num == 0) {
            break;
        }
    }
}

/**
 * Pass messages to and from client.
 * @param clientSocket1  - first client.
 * @param clientSocket2  - second client.
 * @return 1, 2, 0
 */
int ServerFlow::passMessage(int &clientSocket1, int &clientSocket2) {
    int n;
    char buffer[30] = {0};
    n = Server::readSocket(clientSocket1, buffer);
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 0;
    }
    Server::writeSocket(clientSocket2, buffer);
    string play(buffer);
    if (play.find("END_GAME") != string::npos) {
        return 0;
    }
    return 1;
}