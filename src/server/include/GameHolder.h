//
// Created by abby on 26/12/17.
//

#ifndef EX1_GAMEHOLDER_H
#define EX1_GAMEHOLDER_H
#include <iostream>


using namespace std;

using namespace std;

class GameHolder{
private:
    string name;
    int socketPlayer1;
    int socketPlayer2;
    bool joinable;
public:
    GameHolder(string name, int socket);
    string getName();
    int getSocketPLayer1();
    int getSocketPlayer2();
    bool isJoinable();
    void setJoinable(bool flag);
    void setSocketPlayer2(int socketPlayer2);
};
#endif //EX1_GAMEHOLDER_H
