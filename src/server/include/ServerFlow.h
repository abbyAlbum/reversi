//
// Created by abby on 26/12/17.
//

#ifndef EX1_SERVERFLOW_H
#define EX1_SERVERFLOW_H


#include "GameHolder.h"

class ServerFlow {
public:
    ServerFlow(GameHolder *gameHolder);
    void handleClient();
private:
    GameHolder *gh;
    int passMessage(int &clientSocket1, int &clientSocket2);
};

#endif //EX1_SERVERFLOW_H
