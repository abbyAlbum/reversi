//
// Created by abby on 21/11/17.
//

#include "AIPlayer.h"
#include "BasicLogic.h"

/**
 * AIPLayer constructor.
 * @param symbol - the symbol of the AIPlayer.
 * @param board  - the board.
 * @param opp  - the opponent player.
 * @param logic  - the rules of the game.
 */
AIPlayer::AIPlayer(char symbol, Board *board, Player *opp) {
    board_ = board;
    symbol_ = symbol;
    opp_ = opp;
}


Point AIPlayer::makeMove(vector<Point> &moves) {
    int counter = board_->getSize() * board_->getSize() + 1;
    Point temp;
    Player &curr = *this, &oppo = *opp_;
    //go over all the moves for the computer and play them on the copy board
    for(int i = 0; i < moves.size(); i++) {
        Board copyBoard = Board(board_);
        BasicLogic bl = BasicLogic(&copyBoard);
        Point move = Point(moves[i].getX() - 1, moves[i].getY() - 1);
        copyBoard.putChoice(move, curr, oppo);
        //for each move copyboard gets the possible moves of the human player
        vector<Point> moves2 = bl.getPossibleMoves(oppo, curr);
        for(int j = 0; j < moves2.size(); j++) {
            int newCounter = makeHumanPLayerMove(copyBoard, moves2[j]);
            if(newCounter < counter) {
                counter = newCounter;
                move.setPoint(move.getX() + 1, move.getY() + 1);
                temp = move;
            }
            resetCopy(copyBoard);
            copyBoard.putChoice(move, curr, oppo);
        }
    }
    return temp;
}

int AIPlayer:: makeHumanPLayerMove(Board &copyBoard, Point move) {
    move.setPoint(move.getX() - 1, move.getY() - 1);
    copyBoard.putChoice(move, *opp_,*this);
    CellCounter cellCounter = CellCounter(&copyBoard);
    CellCounter &cc = cellCounter;
    cc.count();
    if(symbol_ == 'X') {
        int oCounter = cc.getOCounter() - cc.getXCounter();
        return oCounter;
    }
    if(symbol_ == 'O') {
        int xCounter = cc.getXCounter() - cc.getOCounter();
        return xCounter;
    }
}

char AIPlayer::getSymbol() const {
    return symbol_;
}

void AIPlayer::resetCopy(Board &copy) {
    for (int i = 0; i < board_->getSize(); ++i) {
        for (int j = 0; j < board_->getSize(); ++j) {
            Point p = Point(i, j);
            copy.setStatus(board_->getStatus(p), p);
        }
    }
}