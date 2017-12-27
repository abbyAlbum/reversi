#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>
#include "../include/Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 30

/**
 * THe server constructor.
 * @param port - identify a particular process running on the server
 */
Server::Server(int port, CommandsManager &commandsManager): port(port),
                                                            cm(commandsManager), serverSocket(0) {
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
    vector<pthread_t> threads;
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
        //create a thread
        cout << "Client connected" << endl;
        if (clientSocket == -1) throw "Error on accept";
        pthread_t thread;
        threads.push_back(thread);
        int rc = pthread_create(&thread, NULL, handleClient, (void *)clientSocket);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        // Close communication with the client
        close(clientSocket);
    }
}

/**
 * reads the server socket
 * @param toRead socket to read from
 * @param buffer to read into
 * @return n
 */
int Server::readSocket(int toRead, char buffer[50]) {
    int n = read(toRead, buffer, sizeof(buffer));
    if (n == -1) throw "error reading";
    return n;
}

/**
 * writes to the socket
 * @param toWrite socket to write to
 * @param buffer to write from
 * @return n
 */
int Server::writeSocket(int toWrite, char buffer[50]) {
    int n = write(toWrite, buffer, sizeof(buffer));
    if (n == -1) throw "error writing";
    return n;
}

/**
 * splits up the string that's read, and sends it
 * to commands manager.
 * @param toRead socket to read from
 * @return
 */
void* Server::handleClient(void *toRead) {
    int socketToRead = (int) toRead, index;
    char buffer[50];
    //reads the temp
    Server::readSocket(socketToRead, buffer);
    //split up temp
    string temp(buffer);
    index = temp.find(" ");
    string command = temp.substr(0, index);
    string arg = temp.substr(index, temp.length());
    vector<string> args;
    args.push_back(arg);
    cm.executeCommand(command, args);
}