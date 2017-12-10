//
// Created by eyal on 07/12/17.
//

#ifndef EX1_REMOTEGAME_H
#define EX1_REMOTEGAME_H

#include <stdio.h>
#include "Board.h"
#include "GameLogic.h"
#include "BasicLogic.h"
#include "HumanPlayer.h"
#include "CellCounter.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

class RemoteGame {
public:
    RemoteGame(const char *serverIP, int serverPort, int boardSize);
    void run();
private:
    Board *board_;
    GameLogic *logic_;
    const char *serverIp_;
    int serverPort_;
    int clientSocket_;

    void connectToServer();
    bool readFromServer(Player *curr, Player *opp, int x, int y, CellCounter &cc);
    int playOneTurn(Player *curr, Player *opp, CellCounter &cc, int &i);
    void socketWrite(int x, int y);
};


#endif //EX1_REMOTEGAME_H
