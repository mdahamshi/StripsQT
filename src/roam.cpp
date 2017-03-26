#include "roam.h"

Door Roam::getFirstDoor() const
{
    return firstDoor;
}

void Roam::setFirstDoor(const Door &value)
{
    firstDoor = value;
}

Door Roam::getSecondDoor() const
{
    return secondDoor;
}

void Roam::setSecondDoor(const Door &value)
{
    secondDoor = value;
}

Roam::Roam()
{

}
Roam::Roam(Point a, Point b, int c):Furniture(a,b,c)
{

}
