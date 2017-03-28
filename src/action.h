#ifndef ACTION_H
#define ACTION_H
#include "genpred.h"
#include <list>
#include <math.h>
#include "globavars.h"

class Action
{
public:
    static Building &theBuilding;
    static Building &theGoal;
    int type ,objID ,steps;
    Action(int,int,int);
    Action(const Action &source);
    bool operator==(const Action &source);
    list<Predicate> PreConditions();
    list<Predicate> Deletions();
    list<Predicate> Goals();
    bool doit();
    int euc_dis(int x1, int y1, int x2, int y2);
    Action();
};

#endif // ACTION_H
