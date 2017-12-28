//
// Created by eyal moskowitz 314074303 on 02/11/17.
//

#include <iostream>

#include "../include/Point.h"
using namespace std;

/**
 * empty constructor for Point.
 */
Point::Point() {}

/**
 * constructor for Point.
 * @param x value
 * @param y value
 */
Point::Point(int x, int y) {
    x_ = x;
    y_ = y;
}

/**
 * gets the x value of the point.
 * @return x value
 */
int Point::getX() const { return x_; }

/**
 * gets the y value of the point.
 * @return y value
 */
int Point::getY() const { return y_; }

/**
 * sets the x and y values of the point.
 * @param x value
 * @param y value
 */
void Point::setPoint(int x, int y) {
    x_ = x;
    y_ = y;
}

/**
 * prints the point.
 */
void Point::print() {
    cout << "(" << this->getX() << "," << this->getY() << ")";
}

/**
 * defines == operator for class point.
 *
 * @param p point.
 * @return true if points are equal.
 */
bool Point::operator ==(const Point &p) const {
    return x_ == p.getX() && y_ == p.getY();
}

/**
 * defines operator < for point.
 *
 * @param p point.
 * @return true if this point is smaller than p.
 */
bool Point::operator <(const Point &p) const {
    return x_ < p.getX() ||  (x_ == p.getX() && y_ < p.getY());
}