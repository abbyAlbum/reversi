//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>
#include "Board.h"
#include "GameFlow.h"

using namespace std;

/**
 * main program.
 * @return 0
 */
int main() {
    GameFlow *gf = new GameFlow(8);
    gf->run();
    delete gf;
    return 0;
}