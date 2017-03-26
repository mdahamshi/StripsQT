#ifndef ROAM_H
#define ROAM_H
#include "door.h"

class Roam : public Furniture
{
private:
    Door firstDoor,secondDoor;
public:
    Roam();

    Roam(Point a, Point b, int c);
    Door getFirstDoor() const;
    void setFirstDoor(const Door &value);
    Door getSecondDoor() const;
    void setSecondDoor(const Door &value);
};

#endif // ROAM_H
