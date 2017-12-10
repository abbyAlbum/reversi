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
        cout << "You Win!" << endl;
    else if (cc.getCounter(curr->getSymbol()) < cc.getCounter(opp->getSymbol()))
        cout << "You Lose :(" << endl;
    else cout << "It's a tie!" << endl;
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
    int x, y;
    //will happen every time except for the first player's first turn
    if (i != 1 || curr->getSymbol() != 'X') {
        n = read(clientSocket_, &x, sizeof(int));
        if (n == -1) throw "Error reading from server.";
        n = read(clientSocket_, &y, sizeof(int));
        if (n == -1) throw "Error reading from server.";
        if (x == -2) return 0;
        flag = readFromServer(curr, opp, x, y, cc);
    }
    vector<Point> moves = logic_->getPossibleMoves(*curr, *opp);
    Point choice = curr->makeMove(moves);
    //if current player has no moves left
    if (choice.getX() == -1 && choice.getY() == -1) {
        x = -2, y = -2;
        if (flag || cc.getCounter(' ') == 0) {
            x = choice.getX() - 1;
            y = choice.getY() - 1;
            socketWrite(x, y);
            return 0;
        }
        x = choice.getX();
        y = choice.getY();
        socketWrite(x, y);
        return 1;
    }
    //makes the move.
    choice.setPoint(choice.getX() - 1, choice.getY() - 1);
    x = choice.getX(), y = choice.getY();
    board_->putChoice(choice, *curr, *opp);
    cc.count();
    cout << "Current board:" << endl << endl;
    board_->print();
    cout << "waiting for other player's move" << endl << endl;
    socketWrite(x, y);
    return 1;
}

/**
 * parses the opponent's move from the server
 * @param curr player
 * @param opp player
 * @param point string
 * @return false if player played a move, true if he had no moves
 */
bool RemoteGame::readFromServer(Player *curr, Player *opp, int x, int y, CellCounter &cc) {
    bool flag = false;
    Point choice;
    if (x == -1 && y == -1) flag = true;
    else {
        choice = Point(x, y);
        board_->putChoice(choice, *opp, *curr);
        cc.count();
        cout << "Current board:" << endl << endl;
        board_->print();
        choice.setPoint(choice.getX() + 1, choice.getY() + 1);
        cout << opp->getSymbol() << " played ";
        choice.print();
        cout << endl << endl;
    }
    return flag;
}

void RemoteGame::socketWrite(int x, int y) {
    int n;
    n = write(clientSocket_, &x, sizeof(int));
    if (n == -1) throw "Error writing to socket.";
    n = write(clientSocket_, &y, sizeof(int));
    if (n == -1) throw "Error writing to socket.";
}