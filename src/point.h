#ifndef POINT_H
#define POINT_H
#include <string>

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
    Point & operator=(const Point &source);
    std::string toString();
};

#endif // POINT_H
