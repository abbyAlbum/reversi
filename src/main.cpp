//
// Created by eyal moskowitz 314074303 on 26/10/17.
//
#include <iostream>
#include <fstream>
#include "../include/GameFlow.h"
#include "../include/Menu.h"
#include "../include/RemoteGame.h"
#include "../include/SubMenu.h"
#include "../include/CommandsManager.h"

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
    inFile.open("../exe/client.txt");
    getline(inFile, ip);
    if(!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);
    }
    while(inFile >> x) {
        port = x;
    }
    inFile.close();
    string sOption;
    Menu *menu = new Menu();
    vector<string> listOfGames;
    whichPlayer = menu->runMenu();
//    if (whichPlayer == 3) {
//        SubMenu *sm = new SubMenu();
//        option = sm->runSubMenu();
//        if(option == 1) {
//            sOption.assign("start");
//        }
//        if(option == 2) {
//            sOption.assign("join");
//        }
//        if(option == 3) {
//            sOption.assign("list_games");
//        }
//        CommandsManager *cm = new CommandsManager();
//        cm->executeCommand(sOption, listOfGames);
    if(whichPlayer == 3) {
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
