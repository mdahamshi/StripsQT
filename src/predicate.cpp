#include "predicate.h"
Predicate::Predicate()
{

}
Predicate::Predicate(int x, int y, int id)
{

    objID = id;
    xpos = x;
    ypos = y;
}
bool Predicate::operator ==(const Predicate &source)
{
    return ((objID == source.objID && xpos == source.xpos && ypos == source.ypos));
}
bool Predicate::satisfied()
{
    if(xpos < 1 || xpos >= TOTAL_HEIGHT-1 || ypos < 1 || ypos >= TOTAL_WIDTH -1 )
        return false;
    return (buildingBoard.getStatus(xpos,ypos) == objID);
}

Predicate::Predicate(const Predicate &source)
{
    objID = source.objID;
    xpos = source.xpos;
    ypos = source.ypos;
}
void Predicate::set(int x ,int y ,int id)
{
    objID = id;
    xpos = x;
    ypos = y;
}

void Predicate::print()
{
        if (objID == Globals::WALL)
            std::cout<<"Wall(["<<xpos<<","<<ypos<<"])";
        if(objID == Globals::FREE)
            std::cout<<"Clear(["<<xpos<<","<<ypos<<"])";
        else
            std::cout<<"At("<<objID<<", ["<<xpos<<","<<ypos<<"])";
}
