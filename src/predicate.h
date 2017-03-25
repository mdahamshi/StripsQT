#ifndef PREDICATE_H
#define PREDICATE_H
#include "globals.h"
#include "building.h"
#include "globavars.h"
class Predicate
{
public:
    static Building &theBuilding;
    int xpos, ypos ,objID;
    Predicate();
    Predicate(const Predicate &source);
    bool operator==(const Predicate &source);
    bool satisfied();
    void set(int,int,int);
    void print();
    Predicate(int x ,int y ,int id);

};

#endif // PREDICATE_H
