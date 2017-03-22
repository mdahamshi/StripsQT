#include "genpred.h"

Building &Genpred::theBuilding = Broker::getInstance()->buildingBoard;
Building &Genpred::theGoal = Broker::getInstance()->desiredBoard;
Genpred::Genpred()
{

}

Genpred::Genpred(const Genpred &source)
{
    type = source.type;
    objID = source.objID;
}
Genpred::Genpred(int typ, int id)
{
    type = typ;
    objID = id;
}
bool Genpred::operator ==(const Genpred &source)
{
    return (type == source.type && objID == source.objID);
}
list<Predicate> Genpred::conditions()
{
    list<Predicate> conditionsList;
    int i,j;

            for(i=1; i < TOTAL_HEIGHT -1; i++)
                for(j=1;j < TOTAL_WIDTH -1;j++)
                    if(theBuilding.getStatus(i,j) == objID && theGoal.getStatus(i,j) != objID)
                        conditionsList.push_front(Predicate(i,j,Globals::FREE));
            return conditionsList;
}
list<Genpred> Genpred::expand()
{
    list<Genpred> conditionsList;
    for(int i = 0 ;i < theBuilding.getObjectNum() ;i++)
        conditionsList.push_front(Genpred(ofOBJECT ,i+STARTID));
    return conditionsList;
}
