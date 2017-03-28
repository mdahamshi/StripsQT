#ifndef FURNITURE_H
#define FURNITURE_H
#include "globals.h"
#include "point.h"
class Furniture
{
protected:
    Point topLeft;
    Point downRight;
    int colorIndex;   //also an id
    int roam;
    int lastAct;
public:

    Furniture();
    Furniture(const Furniture& source);
    Furniture(Point,Point,int);
    Furniture(Point,Point,int,int);
    int getWidth();
    int getHeight();
    Point getTopLeftPoint();
    Point getDownRightPoint();
    void setTopLeftPoint(int x ,int y);
    void setDownRightPoint(int x ,int y);
    void print();
    int getRoam() const;
    int getId(){return colorIndex;}
    void setRoam(int value);
    int getLastAct() const;
    void setLastAct(int value);
};

#endif // FURNITURE_H
