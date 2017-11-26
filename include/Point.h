//
// Created by eyal moskowitz 314074303 on 02/11/17.
//

#ifndef EX1_POINT_H
#define EX1_POINT_H


class Point {
private:
    int x_;
    int y_;

public:
    Point();
    Point(int x, int y);
    int getX() const;
    int getY() const;
    void setPoint(int x, int y);
    bool operator ==(const Point &p) const;
    bool operator <(const Point &p) const;
    void print();
};


#endif //EX1_POINT_H
