#ifndef DOOR_H
#define DOOR_H
#include "furniture.h"

class Door : public Furniture
{
private:
    int size;
    int type;
public:

    Door();
    Door(Point a ,Point b );
    int getSize();
    int getType() const;
};

#endif // DOOR_H
