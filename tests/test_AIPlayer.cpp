//
// Created by abby on 28/11/17.
//

#include "../gtest_src/gtest/gtest.h"
#include "../include/AIPlayer.h"

Board b = Board(8);
HumanPlayer p = HumanPlayer('X');
AIPlayer ai = AIPlayer('O', &b, &p);

/**
 * Check that the correct move is returned when human player starts the game
 */
TEST(AIPlayerTest, makeMove) {
    Point po = Point(2, 3);
    b.putChoice(po, p, ai);
    Point p1 = Point(3, 3);
    Point p2 = Point(3, 5);
    Point p3 = Point(5, 3);
    vector<Point> v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    EXPECT_EQ(Point(3, 3), ai.makeMove(v));
}

/**
 * Check that point (-1,-1) is returned if vector os moves is empty
 */
TEST(AIPlayerTest2, makeMove) {
    Point po = Point(2, 3);
    b.putChoice(po, p, ai);
    vector<Point> v;
    EXPECT_EQ(Point(-1, -1), ai.makeMove(v));
}

AIPlayer ai2 = AIPlayer('X', &b, &p);

/**
 * Check that the correct move is returned when AIplayer starts the game
 */
TEST(AIPlayerTest3, makeMove) {
  Point p1 = Point(3, 4);
  Point p2 = Point(4, 3);
  Point p3 = Point(5, 6);
  Point p4 = Point(6, 5);
  vector<Point> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);
  EXPECT_EQ(Point(3, 4), ai2.makeMove(v));
}



