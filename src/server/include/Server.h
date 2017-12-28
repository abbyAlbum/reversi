//
// Created by abby on 08/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include "CommandsManager.h"

typedef struct {
    string name;
    int socket;
}Args;

class Server {
public:
    Server(int port, CommandsManager &commandsManager);
    void start();
    static int readSocket(int toRead, char *buffer);
    static int writeSocket(int toWrite, string s);
    void * handleClient(void *toRead);
private:
    int port;
    int serverSocket; // the socket's file descriptor
    CommandsManager &cm;
};


#endif //UNTITLED1_SERVER_H
