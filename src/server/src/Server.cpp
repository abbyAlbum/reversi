#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <csignal>
#include "../include/Server.h"
#include "../include/GameCollection.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 30

pthread_mutex_t cancel_mutex;
pthread_mutex_t thread_mutex;
/**
 * THe server constructor.
 * @param port_ - identify a particular process running on the server
 */
Server::Server(int port1, CommandsManager &commandsManager) {
    port_ = port1;
    cm = &commandsManager;
    serverSocket_ = 0;
    shouldStop = false;
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
    // Start listening to incoming connections
    listen(serverSocket_, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    Server *s = this;
    pthread_t t;
    int rc = pthread_create(&t, NULL, Server::acceptClients, s);
    if (rc) {
        cout << "Error: unable to create thread, " << rc << endl;
        _exit(-1);
    }
    string exit;
    while (true) {
        cin >> exit;
        if (exit == "exit") {
            setShouldStop();
            stop();
            break;
        }
    }

}

/**
 * changes should stop to true.
 */
void Server::setShouldStop() { shouldStop = true; }

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
        signal(SIGPIPE, SIG_IGN);
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
    int index = -1;
    Args *args = (Args *)arguments;
    string temp = "-1";
    while (index == -1 || temp == "-1") {
        //reads the temp
        temp = "";
        Server::readSocket(args->socket, temp);
        //split up temp
        index = temp.find(" ");
        if (index == -1)
            args->cm->executeCommand(temp, (void *) args);
        else {
            string command = temp.substr(0, index);
            string arg = temp.substr(index + 1, temp.length());
            args->name = arg;
            temp = "";
            temp = checkStrings(command, arg);
            args->cm->executeCommand(command, (void *) args);
        }
    }
}

/**
 * checks if the command we got was valid.
 * @param command
 * @param name of game
 * @return "-1" if command is bad and "okay" otherwise
 */
string Server::checkStrings(string &command, string &name) {
    GameCollection *gc = GameCollection::getInstance();
    bool flag = false;
    if (command == "start") {
        for (int i = 0; i < gc->getList().size(); ++i) {
            if (name == gc->getList()[i].getName())
                flag = true;
        }
    } else {
        for (int i = 0; i < gc->getList().size(); ++i) {
            if (name == gc->getList()[i].getName() && !gc->getList()[i].isJoinable())
                flag = true;
        }
    }
    if (flag) return "-1";
    else return "okay";
}

/**
 * waits for exit command from user
 * @param server to use the server
 * @return
 */
void Server::stop() {
    GameCollection *gc = GameCollection::getInstance();
    pthread_mutex_lock(&cancel_mutex);
    for (int i = 0; i < gc->getList().size(); i++)
        cm->executeCommand("close", &gc->getList()[i]);
    for (int i = 0; i < threads.size(); i++) {
        pthread_cancel(threads[i]);
        pthread_mutex_unlock(&cancel_mutex);
    }
    close(serverSocket_);
}

/**
 * accepts clients
 * @param v server variable
 * @return
 */
void* Server::acceptClients(void *v) {
    Server *s = (Server *) v;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;
    cout << "Waiting for client connections..." << endl;
    while (!s->shouldStop) {
        // Accept a new client connection
        int clientSocket = accept(s->serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
        if (clientSocket == -1) throw "Error on accept";
        //create a thread
        cout << "Client connected" << endl;
        pthread_t thread;
        Args *args = new Args();
        args->cm = s->cm;
        args->socket = clientSocket;
        int rc = pthread_create(&thread, NULL, Server::handleClient, (void *) args);
        if (rc) {
            cout << "Error: unable to create thread, " << rc << endl;
            _exit(-1);
        }
        pthread_mutex_lock(&thread_mutex);
        s->threads.push_back(thread);
        pthread_mutex_unlock(&thread_mutex);
    }
}