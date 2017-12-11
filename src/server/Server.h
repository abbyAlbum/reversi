//
// Created by abby on 08/12/17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

class Server {
public:
    Server(int port);
    void start();
private:
    int port;
    int serverSocket; // the socket's file descriptor
    void handleClient(int clientSocket, int clientSocket2);
    int passMessage(int &clientSocket1, int &clientSocket2);
};


#endif //UNTITLED1_SERVER_H
