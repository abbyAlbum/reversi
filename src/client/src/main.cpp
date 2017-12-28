//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>
#include <fstream>
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
    ifstream inFile;
    int port = 0;
    int x;
    string ip;
    //read from the file to get the port number for the server
    inFile.open("../exe/client.txt");
    getline(inFile, ip);
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    while (inFile >> x) {
        port = x;
    }
    inFile.close();
    Menu *menu = new Menu();
    whichPlayer = menu->runMenu();
    if (whichPlayer == 3) {
        RemoteGame *rg = new RemoteGame(ip.c_str(), port, DEFAULT_SIZE);
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
