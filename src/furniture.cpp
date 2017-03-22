#include "furniture.h"

Furniture::Furniture()
{

}

Furniture::Furniture(Point a ,Point b, int c)
{
    this->topLeft = a;
    this->downRight = b;
    this->colorIndex = c;
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
    std::cout<<"Furnituer: id= "<<colorIndex<<" x1,y1 "<<topLeft.x<<","<<topLeft.y<<" x2,y2 "<<downRight.x<<","<<downRight.y
            <<" width: "<<getWidth()<<" height: "<<getHeight()<<"."<<std::endl;
}

Point Furniture::getTopLeftPoint()
{
    return topLeft;
}
Point Furniture::getDownRightPoint()
{
    return downRight;
}
