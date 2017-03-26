#ifndef DOOR_H
#define DOOR_H
#include "furniture.h"

class Door : public Furniture
{
public:
    int size;
    Door();
    Door(Point a ,Point b );
    int getSize();
};

#endif // DOOR_H
