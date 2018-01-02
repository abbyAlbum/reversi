//
// Created by eyal on 07/12/17.
//

#include "../include/RemoteGame.h"
#include "../include/SubMenu.h"

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

/**
 * Connects to the server.
 */
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
    int i = 1, endGame, color;
    SubMenu sm;
    connectToServer();
    color = commandAndColor(sm);
    if (!color) {
        cout << "Server is going to shut down so game over" << endl << endl;
        return;
    }
    Player *curr = new HumanPlayer(color);
    Player *opp = new HumanPlayer(3 - color);
    CellCounter cc = CellCounter(board_);
    while (true) {
        //prints the board at the beginning for the first player only
        if (i == 1 && curr->getSymbol() == 'X') board_->print();
        endGame = playOneTurn(curr, opp, cc, i);
        if (!endGame || endGame == -1) break;
        i++;
    }
    if (endGame) cout << "Server is going to shut down so game over" << endl << endl;
    else {
        if (cc.getCounter(curr->getSymbol()) > cc.getCounter(opp->getSymbol()))
            cout << "You Win!" << endl;
        else if (cc.getCounter(curr->getSymbol()) < cc.getCounter(opp->getSymbol()))
            cout << "You Lose :(" << endl;
        else cout << "It's a tie!" << endl;
    }
    delete curr;
    delete opp;
}

/**
 * Splits the args to get the first part
 * @param args - the command and anme
 * @return the command
 */
string RemoteGame::getCommand(string args) {
    int index = args.find(" ");
    string command = args.substr(0, index);
    return command;
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
    string play;
    //will happen every time except for the first player's first turn
    if (i != 1 || curr->getSymbol() != 'X') {
        n = socketRead(play);
        if (n) return -1;
        if (play.find("END_GAME") != string::npos) return 0;
        flag = readFromServer(curr, opp, play, cc);
    }
    vector<Point> moves = logic_->getPossibleMoves(*curr, *opp);
    Point choice = curr->makeMove(moves);
    // if current player has no moves left
    if (choice.getX() == -1 && choice.getY() == -1) {
        if (flag || cc.getCounter(' ') == 0) {
            n = socketWrite("END_GAME");
            if (n) return -1;
            return 0;
        }
        n = socketWrite("NO_MOVES");
        if (n) return -1;
        return 1;
    }
    //makes the move.
    choice.setPoint(choice.getX() - 1, choice.getY() - 1);
    play = "";
    int x = choice.getX(), y = choice.getY();
    //play = choice.getX() + " " + choice.getY();
    ostringstream geek;
    geek << x;
    play = geek.str() + " ";
    geek.str("");
    geek.clear();
    geek << y;
    play += geek.str();
    //play =  + " " + y;
    board_->putChoice(choice, *curr, *opp);
    cc.count();
    cout << "Current board:" << endl << endl;
    board_->print();
    cout << "waiting for other player's move" << endl << endl;
    n = socketWrite(play);
    if (n) return -1;
    return 1;
}

/**
 * parses the opponent's move from the server
 * @param curr player
 * @param opp player
 * @param point string
 * @return false if player played a move, true if he had no moves
 */
bool RemoteGame::readFromServer(Player *curr, Player *opp, string &play, CellCounter &cc) {
    bool flag = false;
    Point choice;
    if (play == "NO_MOVES") {
        flag = true;
        cout << "Current Board:" << endl << endl;
        board_ ->print();
        cout << opp->getSymbol() << " had no moves." << endl << endl;
    }
    else {
        choice = stringToPoint(play);
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

/**
 * Writes to the socket
 * @param x - x point
 * @param y  - y point
 */
int RemoteGame::socketWrite(string s) {
    char buffer;
    int i = 0, n;
    do {
        buffer = s.at(i);
        n = write(clientSocket_, &buffer, sizeof(char));
        if (n == -1) return n;
        i++;
    } while (i < s.length());
    buffer = '\0';
    n = write(clientSocket_, &buffer, sizeof(char));
    if (n == -1) return n;
    return 0;
}

/**
 * reads from the socket.
 * @param buffer to read into
 */
int RemoteGame::socketRead(string &s) {
    int i = 0, n;
    char buffer;
    do {
        n = read(clientSocket_, &buffer, sizeof(char));
        if (n == -1) return n;
        if (buffer == '\0') break;
        s += buffer;
        i++;
    } while (true);
    if (s == "\0") return -1;
    return 0;
}

/**
 * does the command the user uses and gives him his color at the end.
 * @param sm sub menu
 * @return the color or 0 if server disconnected.
 */
int RemoteGame::commandAndColor(SubMenu &sm) {
    int n, color;
    string command, args, buffer, colour;
    do {
        args = sm.runSubMenu();
        //write command to the socket
        n = socketWrite(args);
        if (n) return 0;
        command = getCommand(args);
        //read answer from the server
        n = socketRead(buffer);
        if (n) return 0;
        if (buffer == "-1") cout << "try again with a different name" << endl << endl;
        else cout << buffer << endl;
    } while (command == "list_games" || buffer == "-1");
    // if we have joined a game or started a game correctly
    string name = getGameName(args);
    // reading the number that represents the colour
    n = socketRead(colour);
    if (n) return 0;
    if (colour[0] == 'b')
        color = 1;
    else
        color = 2;
    return color;
}

/**
 * converts a string to a point
 * @param s string to convert
 * @return point
 */
Point RemoteGame::stringToPoint(string s) {
    int x, y, index = s.find(" ");
    string xCoor = s.substr(0, index);
    string yCoor = s.substr(index, s.length() - 1);
    stringstream(xCoor) >> x;
    stringstream(yCoor) >> y;
    return Point(x, y);
}

/**
 * gets the name of the current game
 * @param args
 * @return game name
 */
string RemoteGame::getGameName(string &args) {
    int index = args.find(" ");
    return args.substr(index, args.length() - 1);
}

/**
 * Deconstructor.
 */
RemoteGame::~RemoteGame() {
    delete board_;
    delete logic_;
    close(clientSocket_);
}