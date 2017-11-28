//
// Created by abby on 26/11/17.
//

#include "../gtest_src/gtest/gtest.h"
#include "../include/BasicLogic.h"
#include "../include/HumanPlayer.h"

Board b = Board(8);
BasicLogic bl = BasicLogic(&b);
HumanPlayer player1 = HumanPlayer('X');
HumanPlayer player2 = HumanPlayer('O');

/**
 * checks that the check funcs return the right points.
 */
TEST(BasicLogicTest, CheckAround) {
    EXPECT_TRUE(bl.checkUp(3, 3, player1, player2) == Point(3, 4));
    EXPECT_TRUE(bl.checkDown(4, 4, player1, player2) == Point(6, 5));
    EXPECT_EQ(bl.checkRight(4, 4, player1, player2), Point(5, 6));
    EXPECT_EQ(bl.checkDownL(3, 4, player1, player2), Point(-1, -1));
    EXPECT_EQ(bl.checkLeft(4, 3, player2, player1), Point(5, 3));
    EXPECT_EQ(bl.checkUpR(3, 4, player1, player2), Point(-1, -1));
    EXPECT_EQ(bl.checkDownR(3, 3, player2, player1), Point(-1, -1));
    EXPECT_EQ(bl.checkUpL(4, 4, player2, player1), Point(-1, -1));
}

/**
 * checks the vector by comparing its size.
 */
TEST(BasicLogicTest, CheckMovesVector) {
    EXPECT_EQ(bl.getPossibleMoves(player1, player2).size(), 4);
    Point p = Point(2, 3);
    b.putChoice(p, player1, player2);
    EXPECT_EQ(bl.getPossibleMoves(player2, player1).size(), 3);
}