#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "../include/Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 10

/**
 * THe server constructor.
 * @param port - identify a particular process running on the server
 */
Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}

/**
 * Starts the server
 */
void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        int num = 3;
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        //create a thread
        int n = write(clientSocket, &num, sizeof(int));
        int clientSocket2 = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1) {
            throw "Error on accept";
        }
       handleClient(clientSocket, clientSocket2);
        // Close communication with the client
        close(clientSocket);
        close(clientSocket2);
    }
}


int Server::readSocket(int toRead, char *buffer) {
    int n = read(toRead, buffer, sizeof(buffer));
    if (n == -1) throw "error reading";
    return n;
}

int Server::writeSocket(int toWrite, char *buffer) {
    int n = write(toWrite, buffer, sizeof(buffer));
    if (n == -1) throw "error writing";
    return n;

}