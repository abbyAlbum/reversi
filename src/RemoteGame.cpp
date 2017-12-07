//
// Created by eyal on 07/12/17.
//

#include "../include/RemoteGame.h"

/**
 * c'tor for RemoteGame
 * @param serverIP
 * @param serverPort
 * @param boardSize
 */
RemoteGame::RemoteGame(const char *serverIP, int serverPort, int boardSize) {
    serverIp_ = serverIP;
    serverPort_ = serverPort;
    board_ = new Board(boardSize);
    logic_ = new BasicLogic(board_);
}

void RemoteGame::connectToServer() {
    // Create a socket point
    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket_ == -1) throw "Error opening socket";
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIp_, &address)) throw "Can't parse IP address";
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
    if (server == NULL) throw "Host is unreachable";
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, server -> h_addr, server -> h_length);
    //htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort_);
    // Establish a connection with the TCP server
    if (connect(clientSocket_, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
        throw "Error connecting to server";
    cout << "Connected to server." << endl;
}

/**
 * runs the online game
 */
void RemoteGame::run() {
    int n, color, i = 1, endGame;
    connectToServer();
    //reading the number that represents the color
    n = read(clientSocket_, &color, sizeof(color));
    if (n == -1) throw "Error reading from server.";
    Player *curr = new HumanPlayer(color);
    Player *opp = new HumanPlayer(3 - color);
    CellCounter cc = CellCounter(board_);
    while (true) {
        //prints the board at the beginning for the first player only
        if (i == 1 && curr->getSymbol() == 'X') board_->print();
        endGame = playOneTurn(curr, opp, cc, i);
        if (endGame == 0 || cc.getCounter(' ') == 0) break;
        i++;
    }
    if (cc.getCounter(curr->getSymbol()) > cc.getCounter(opp->getSymbol()))
        cout << "You Win! with " << endl;
    else if (cc.getCounter(curr->getSymbol()) < cc.getCounter(opp->getSymbol()))
        cout << "You Lose :(" << endl;
    else cout << "It's a tie! gg" << endl;
}

/**
 * plays a turn online
 * @param curr player
 * @param opp player
 * @param cc counter
 * @param i to know which turn it is
 * @return 1 to continue the game 0 otherwise
 */
int RemoteGame::playOneTurn(Player *curr, Player *opp, CellCounter &cc, int &i) {
    int n;
    bool flag = false;
    string point;
    //will happen every time except for the first player's first turn
    if (i != 1 || curr->getSymbol() != 'X') {
        n = read(clientSocket_, &point, sizeof(point));
        if (n == -1) throw "Error reading from server.";
        if (!strcmp(point.c_str(), "end")) return 0;
        flag = readFromServer(curr, opp, point);
    }
    vector<Point> moves = logic_->getPossibleMoves(*curr, *opp);
    Point choice = curr->makeMove(moves);
    //if current player has no moves left
    if (choice.getX() == -1) {
        if (flag) {
            n = write(clientSocket_, "end", END_SIZE);
            if (n == -1) throw "Error writing to socket.";
            return 0;
        }
        else n = write(clientSocket_, "NoMove", NO_MOVE_SIZE);
        if (n == -1) throw "Error writing to socket.";
    }
    //makes the move.
    choice.setPoint(choice.getX() - 1, choice.getY() - 1);
    board_->putChoice(choice, *curr, *opp);
    cc.count();
    cout << "Current board:" << endl << endl;
    board_->print();
    cout << "waiting for other player's move" << endl << endl;
    n = write(clientSocket_, choice.getX() + "," + choice.getY(), POINT_SIZE);
    if (n == -1) throw "Error writing to socket.";
    return 1;
}

/**
 * parses the opponent's move from the server
 * @param curr player
 * @param opp player
 * @param point string
 * @return false if player played a move, true if he had no moves
 */
bool RemoteGame::readFromServer(Player *curr, Player *opp, string &point) {
    bool flag = false;
    Point choice;
    if (!strcmp(point.c_str(), "NoMove")) flag = true;
    else {
        int x = (int) point[0];
        int y = (int) point[2];
        choice = Point(x, y);
        board_->putChoice(choice, *opp, *curr);
        cout << "Current board:" << endl << endl;
        board_->print();
        choice.setPoint(choice.getX() + 1, choice.getY() + 1);
        cout << opp->getSymbol() << " played ";
        choice.print();
        cout << endl << endl;
    }
    return flag;
}