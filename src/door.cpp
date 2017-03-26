#include "door.h"

Door::Door()
{

}

Door::Door(Point a, Point b)
{
    topLeft = a <= b ? a : b;
    downRight = a >= b ? b : a;
    size = getWidth() > getHeight() ? getWidth() : getHeight();
}

int Door::getSize()
{
    return size;
}
