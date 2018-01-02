#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "../include/Server.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 30

/**
 * THe server constructor.
 * @param port_ - identify a particular process running on the server
 */
Server::Server(int port1, CommandsManager &commandsManager) {
    port_ = port1;
    cm = &commandsManager;
    serverSocket_ = 0;
    cout << "Server" << endl;
}

/**
 * Starts the server
 */
void Server::start() {
    // Create a socket point
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port_);
    if (bind(serverSocket_, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    vector<pthread_t> threads;
    // Start listening to incoming connections
    listen(serverSocket_, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    cout << "Waiting for client connections..." << endl;
    while (true) {
        // Accept a new client connection
        int clientSocket = accept(serverSocket_, (struct sockaddr *)&clientAddress, &clientAddressLen);
        //create a thread
        cout << "Client connected" << endl;
        if (clientSocket == -1) throw "Error on accept";
        pthread_t thread;
        Args *args = new Args();
        args->cm = cm;
        args->socket = clientSocket;
        int rc = pthread_create(&thread, NULL, Server::handleClient, (void *)args);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            exit(-1);
        }
        //pthread_join(thread, NULL);
        threads.push_back(thread);
    }
}

/**
 * reads the servery socket
 * @param toRead socket to read from
 * @param buffer to read into
 * @return n
 */
int Server::readSocket(int toRead, string &args) {
    int i = 0, n;
    char buffer;
    do {
        n = read(toRead, &buffer, sizeof(char));
        if (n == -1) throw "error reading";
        if (buffer == '\0') break;
        args += buffer;
        i++;
    } while (true);
    return n;
}

/**
 * writes to the socket
 * @param toWrite socket to write to
 * @param buffer to write from
 * @return n
 */
int Server::writeSocket(int toWrite, string args) {
    char buffer;
    int i = 0, n;
    do {
        buffer = args.at(i);
        n = write(toWrite, &buffer, sizeof(char));
        if (n == -1) throw "error reading";
        i++;
    } while (i < args.length());
    buffer = '\0';
    n = write(toWrite, &buffer, sizeof(char));
    if (n == -1) throw "error reading";
    return n;
}

/**
 * splits up the string that's read, and sends it
 * to commands manager.
 * @param toRead socket to read from
 * @return
 */
void* Server::handleClient(void *arguments) {
    int index;
    Args *args = (Args *)arguments;
    string temp;
    //reads the temp
    Server::readSocket(args->socket, temp);
    //split up temp
    index = temp.find(" ");
    if (index == -1)
        args->cm->executeCommand(temp, (void *)args);
    else {
        string command = temp.substr(0, index);
        string arg = temp.substr(index + 1, temp.length());
        args->name = arg;
        args->cm->executeCommand(command, (void *) args);
    }
}
