//
// Created by abby on 28/11/17.
//

#include "../gtest_src/gtest/gtest.h"
#include "../include/Board.h"

Board board1 = Board(8);

/**
 * Check the the board input is correct - true
 */
TEST(BoardTest, BoardStatusCheck) {
    EXPECT_TRUE(board1.getStatus(Point(3, 4)) == 'X');
    EXPECT_TRUE(board1.getStatus(Point(4, 4)) == 'O');
}

/**
 * Check the the board input is correct - false
 */
TEST(BoardTest2, BoardStatusCheck) {
    EXPECT_FALSE(board1.getStatus(Point(6, 6)) == 'O');
    EXPECT_FALSE(board1.getStatus(Point(7, 5)) == 'X');
}