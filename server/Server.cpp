#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Server.h"

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
    // StartCommand listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        int num = 3;
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
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



/**
 * Handle requests from a specific client
 * @param clientSocket - the first client socket.
 * @param clientSocket2 - the second client socket.
 */
void Server::handleClient(int clientSocket, int clientSocket2) {
    int counter = 1;
    int num;
    int n;
    int first, second;
    first = 1;
    second = 2;
    //tell the clients which player they are, depending on who joined first
    n = write(clientSocket, &first, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
    n = write(clientSocket2, &second, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
    while (true) {
        if (counter % 2 == 1)
            num = passMessage(clientSocket, clientSocket2);
        else
            num = passMessage(clientSocket2, clientSocket);
        counter++;
        if(num == 0 || num == 2) {
            break;
        }
    }
}

/**
 * Pass messages to and from client.
 * @param clientSocket1  - first client.
 * @param clientSocket2  - second client.
 * @return 1, 2, 0
 */
int Server:: passMessage(int &clientSocket1, int &clientSocket2) {
    int n;
    int x, y;
    n = read(clientSocket1, &x, sizeof(int));
    if (n == -1) {
        cout << "Error reading X" << endl;
        return 2;
    }
    n = read(clientSocket1, &y, sizeof(int));
    if (n == -1) {
        cout << "Error reading X" << endl;
        return 2;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return 0;
    }
    n = write(clientSocket2, &x, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
    n = write(clientSocket2, &y, sizeof(int));
    if (n == -1) {
        cout << "Error writing to socket" << endl;
    }
    if (x == -2 && y == -2) {
        return 0;
    }
    return 1;
}