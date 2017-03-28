#include "door.h"

int Door::getType() const
{
    return type;
}





Door::Door()
{

}

Door::Door(Point a, Point b)
{
    topLeft = a <= b ? a : b;
    downRight = a >= b ? a : b;
    size = getHeight() > getWidth() ? getHeight() : getWidth();
    type = getHeight() > getWidth() ? Globals::VER : Globals::HOR;

}

int Door::getSize()
{
    return size;
}
