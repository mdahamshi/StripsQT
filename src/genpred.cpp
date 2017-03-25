#include "genpred.h"


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
                    if(buildingBoard.getStatus(i,j) == objID && desiredBoard.getStatus(i,j) != objID){
                        conditionsList.push_front(Predicate(i,j,Globals::FREE));
                    }
            return conditionsList;
}
list<Genpred> Genpred::expand()
{
    list<Genpred> conditionsList;
    for(int i = 0 ;i < buildingBoard.getObjectNum() ;i++)
        conditionsList.push_front(Genpred(ofOBJECT ,i+STARTID));
    return conditionsList;
}
