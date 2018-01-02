#include "../include/Server.h"
#include "../include/GameCollection.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
    ifstream inFile;
    int port = 0;
    int x;
    //read from the file to get the port number for the server
    inFile.open("../exe/server.txt");
    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    while (inFile >> x) {
        port = x;
    }
    inFile.close();
    CommandsManager *cm = CommandsManager::getInstance();
    GameCollection *gc = GameCollection::getInstance();
    Server server(port, *cm);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
    delete gc;
}