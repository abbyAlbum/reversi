//
// Created by abby on 08/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "CommandsManager.h"

typedef struct {
    string name;
    int socket;
    CommandsManager *cm;
}Args;

class Server {

public:
    Server(int port, CommandsManager &commandsManager);
    void start();
    static int readSocket(int toRead, string &args);
    static int writeSocket(int toWrite, string s);
    static void * handleClient(void *arguments);
private:
    int port_;
    int serverSocket_; // the socket's file descriptor
    CommandsManager *cm;
};


#endif //UNTITLED1_SERVER_H

