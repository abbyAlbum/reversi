//
// Created by abby on 08/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

class Server {
public:
    Server(int port);
    void start();
    static int readSocket(int toRead, char *buffer);
    static int writeSocket(int toWrite, char *buffer);
private:
    int port;
    int serverSocket; // the socket's file descriptor
};


#endif //UNTITLED1_SERVER_H
