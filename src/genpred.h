#ifndef GENPRED_H
#define GENPRED_H
#include <iostream>
#include <list>
#include "broker.h"
class Genpred
{
public:
    static Building &theBuilding;
    static Building &theGoal;
    int type ,objID;
    Genpred();
    Genpred(int typ ,int id);
    Genpred(const Genpred &source);
    bool operator==(const Genpred &source);
    list<Predicate> conditions();
    list<Genpred> expand();
};

#endif // GENPRED_H
