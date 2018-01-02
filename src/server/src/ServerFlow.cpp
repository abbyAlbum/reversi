//
// Created by abby on 26/12/17.
//

#include "../include/ServerFlow.h"
#include "../include/Server.h"
#include <cstring>

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

    firstSocket = gh->getSocketPLayer1();
    secondSocket = gh->getSocketPlayer2();
    //tell the clients which player they are, depending on who joined first
    Server::writeSocket(firstSocket, "black");
    Server::writeSocket(secondSocket, "white");
    while (true) {
        if (counter % 2 == 1)
            num = passMessage(firstSocket, secondSocket);
        else
            num = passMessage(secondSocket, firstSocket);
        counter++;
        if(num == 0) {
            CommandsManager *cm = CommandsManager::getInstance();
            cm->executeCommand("close", gh);
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
    string play;
    n = Server::readSocket(clientSocket1, play);
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 0;
    }
    Server::writeSocket(clientSocket2, play);
    if (play == "END_GAME") {
        return 0;
    }
    return 1;
}