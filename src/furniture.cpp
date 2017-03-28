#include "furniture.h"

int Furniture::getRoam() const
{
    return roam;
}

void Furniture::setRoam(int value)
{
    roam = value;
}

int Furniture::getLastAct() const
{
    return lastAct;
}

void Furniture::setLastAct(int value)
{
    lastAct = value;
}

Furniture::Furniture()
{

}

Furniture::Furniture(Point a ,Point b, int c)
{
    this->topLeft = a;
    this->downRight = b;
    this->colorIndex = c;
}
Furniture::Furniture(Point a ,Point b, int c,int roamidd)
{
    this->topLeft = a;
    this->downRight = b;
    this->colorIndex = c;
    this->roam = roamidd;
}
int Furniture::getWidth()
{
    return downRight.y - topLeft.y + 1;
}
int Furniture::getHeight()
{
     return downRight.x - topLeft.x + 1;
}
Furniture::Furniture(const Furniture &source)
{
    this->colorIndex = source.colorIndex;
    this->downRight = source.downRight;
    this->topLeft = source.topLeft;
    this->roam = source.roam;
    this->lastAct = source.lastAct;
}
void Furniture::setTopLeftPoint(int x, int y)
{
    topLeft.x = x;
    topLeft.y = y;
}
void Furniture::setDownRightPoint(int x, int y)
{
    downRight.x = x;
    downRight.y =y;
}

void Furniture::print()
{
    //std::cout<<"Furnituer: id= "<<colorIndex<<" x1,y1 "<<topLeft.x<<","<<topLeft.y<<" x2,y2 "<<downRight.x<<","<<downRight.y
            <<" width: "<<getWidth()<<" height: "<<getHeight()<<" . roamid:"<<getRoam()<<std::endl;
}

Point Furniture::getTopLeftPoint()
{
    return topLeft;
}
Point Furniture::getDownRightPoint()
{
    return downRight;
}
