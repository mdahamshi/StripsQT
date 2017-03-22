#ifndef FURNITURE_H
#define FURNITURE_H
#include "globals.h"
#include "point.h"
class Furniture
{
private:
    Point topLeft;
    Point downRight;
    int colorIndex;   //also an id
public:

    Furniture();
    Furniture(const Furniture& source);
    Furniture(Point,Point,int);
    int getWidth();
    int getHeight();
    Point getTopLeftPoint();
    Point getDownRightPoint();
    void setTopLeftPoint(int x ,int y);
    void setDownRightPoint(int x ,int y);
    void print();
};

#endif // FURNITURE_H
