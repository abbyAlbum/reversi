//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>
#include "./include/GameFlow.h"
#include "./include/Menu.h"

using namespace std;

/**
 * main program.
 * @return 0
 */
int main() {
    int whichPlayer;
    Menu *menu = new Menu();
    if (!(whichPlayer = menu->runMenu()))
        return 0;
    GameFlow *gf = new GameFlow(menu->getBoardSize());
    gf->run(menu->getPlayer(), whichPlayer, menu->getSymbol());
    delete menu;
    delete gf;
    return 0;
}