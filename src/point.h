#ifndef POINT_H
#define POINT_H


class Point
{
public:
    int x;
    int y;
    Point();
    Point(int,int);
    bool operator<(const Point &source);
    bool operator>(const Point&);
    bool operator<=(const Point &source);
    bool operator>=(const Point&);
};

#endif // POINT_H
