//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>
#include "../include/GameFlow.h"
#include "../include/Menu.h"
#include "../include/RemoteGame.h"

using namespace std;

/**
 * main program.
 * @return 0
 */
int main() {
    int whichPlayer;
    Menu *menu = new Menu();
    whichPlayer = menu->runMenu();
    if (whichPlayer == 3) {
        RemoteGame *rg = new RemoteGame("127.0.0.1", 3064, 4);
        rg->run();
        delete rg;
    } else {
        GameFlow *gf = new GameFlow(menu->getBoardSize());
        gf->run(menu->getPlayer(), whichPlayer, menu->getSymbol());
        delete gf;
    }
    delete menu;
    return 0;
}
