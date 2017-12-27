//
// Created by abby on 26/12/17.
//

#ifndef EX1_GAMECOLLECTION_H
#define EX1_GAMECOLLECTION_H

#include <iostream>
#include <vector>
#include "Command.h"
#include "GameHolder.h"


using namespace std;

class GameCollection{
private:
    vector<GameHolder> log;
public:
    GameCollection();
    void add(GameHolder gh);
    void remove(string name);
    vector<GameHolder> getList();
};



#endif //EX1_GAMECOLLECTION_H
