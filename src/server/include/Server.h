//
// Created by abby on 08/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "CommandsManager.h"



class Server {

public:
    Server(int port_, CommandsManager &commandsManager);
    void start();
    static int readSocket(int toRead, char *buffer);
    static int writeSocket(int toWrite, string s);
    static void * handleClient(void *arguments);
private:
    int port_;
    int serverSocket_; // the socket's file descriptor
    CommandsManager *cm;
};


#endif //UNTITLED1_SERVER_H
