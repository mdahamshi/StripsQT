#include "action.h"
Building &Action::theBuilding = Broker::getInstance()->buildingBoard;
Building &Action::theGoal = Broker::getInstance()->desiredBoard;
Action::Action()
{

}
Action::Action(int typ, int id)
{
    objID = id;
    type = typ;
}
Action::Action(const Action &source)
{
    objID = source.objID;
    type = source.type;
}
bool Action::operator ==(const Action &source)
{
    return (type == source.type && objID == source.objID);
}
list<Predicate> Action::PreConditions()
{
    //initialization
    int i,j,x_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().x,y_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().x,x_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().y;
    int l=y_bottomright-y_topleft;
    int w=x_bottomright-x_topleft;
    int R=floor(sqrt((double)(w+1)*(w+1)+(l+1)*(l+1)))+1; //radious for rtotation
    list<Predicate> reqPreCond = list<Predicate>();

    switch (type) {
    case MOVE_RIGHT:
        for(i=x_topleft; i <= x_bottomright; i++)
            reqPreCond.insert(reqPreCond.end(),Predicate(i , y_bottomright+1, Globals::FREE));
        break;

    case MOVE_LEFT:
        for(i=x_topleft; i <= x_bottomright; i++)
            reqPreCond.insert(reqPreCond.end(),Predicate(i , y_topleft-1, Globals::FREE));
            break;

    case MOVE_UP:
        for(j=y_topleft; j <= y_bottomright; j++)
            reqPreCond.insert(reqPreCond.end(),Predicate(x_topleft-1 , j, Globals::FREE));
            break;

    case MOVE_DOWN:
        for(j=y_topleft; j <= y_bottomright; j++)
            reqPreCond.insert(reqPreCond.end(),Predicate(x_bottomright + 1 , j, Globals::FREE));
            break;

    case ROTATE_RIGHT:
        for(i=x_bottomright; i>=x_topleft; i--)
            for(j=y_topleft-1; j>=y_topleft-w-1; j--)
                if(euc_dis(x_topleft, y_topleft, i, j)<R)
                    reqPreCond.insert(reqPreCond.end(),Predicate(i , j, Globals::FREE));
        for(i=x_topleft+R+1; i>=x_bottomright+1; i--)
            for(j=y_bottomright; j>=y_topleft-w-1; j--)
                if(euc_dis(x_topleft, y_topleft, i, j)<R)
                    reqPreCond.insert(reqPreCond.end(),Predicate(i , j, Globals::FREE));

            break;

    case ROTATE_LEFT:
        for(i=x_bottomright; i>=x_topleft-l; i--)
            for(j=y_topleft+R; j>=y_bottomright+1; j--)
                if(euc_dis(x_topleft, y_topleft, i, j)<R)
                    reqPreCond.insert(reqPreCond.end(),Predicate(i , j, Globals::FREE));
        for(i=x_topleft-1; i>=x_topleft-l-1; i--)
            for(j=y_bottomright+w; j>=y_topleft; j--)
                if(euc_dis(x_topleft, y_topleft, i, j)<R)
                    reqPreCond.insert(reqPreCond.end(),Predicate(i , j, Globals::FREE));

            break;

    default:
        break;
    }
    return reqPreCond;

}
int Action::euc_dis(int x1, int y1, int x2, int y2)
{
    return floor(sqrt((double)(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

list<Predicate> Action::Deletions()
{
    //initialization
    int i,j,x_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().x,y_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().x,x_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().y;

    list<Predicate> delList = list<Predicate>();
    Predicate pred;
    switch (type) {
            case MOVE_RIGHT:
                for(i=x_bottomright; i>=x_topleft; i--)
                {
                    pred=Predicate(i,y_bottomright+1,Globals::FREE);
                    if(pred.satisfied())
                        delList.push_back(pred);
                    pred=Predicate(i,y_topleft,Globals::FREE);
                    delList.remove(pred);
                }
                break;
            case MOVE_LEFT:
                for(i=x_bottomright; i>=x_topleft; i--)
                {
                    pred=Predicate(i,y_bottomright-1,Globals::FREE);
                    if(pred.satisfied())
                        delList.push_back(pred);
                    pred=Predicate(i,y_topleft,Globals::FREE);
                    delList.remove(pred);
                }
                    break;
            case MOVE_UP:
                for(j=y_bottomright; j>=y_topleft; j--)
                {
                    pred=Predicate(x_topleft-1,j,Globals::FREE);
                    if(pred.satisfied())
                        delList.push_back(pred);
                    pred=Predicate(x_bottomright,j,Globals::FREE);
                    delList.remove(pred);
                }
                break;
            case MOVE_DOWN:
                for(j=y_bottomright; j>=y_topleft; j--)
                {
                    pred=Predicate(x_topleft+1,j,Globals::FREE);
                    if(pred.satisfied())
                        delList.push_back(pred);
                    pred=Predicate(x_bottomright,j,Globals::FREE);
                    delList.remove(pred);
                }
                break;
            case ROTATE_RIGHT:
                for(i=x_topleft-1; i>=x_topleft-y_bottomright+y_topleft-1; i--)
                    for(j=y_topleft-1; j>=y_topleft-x_bottomright+x_topleft-1; j--)
                    {
                        pred=Predicate(i,j,Globals::FREE);
                        if(pred.satisfied())
                            delList.push_back(pred);
                    }
                break;
            case ROTATE_LEFT:
                for(i=x_topleft-1; i>=x_topleft-y_bottomright+y_topleft-1; i--)
                    for(j=y_topleft+x_bottomright-x_topleft; j>=y_topleft; j--)
                    {
                        pred=Predicate(i,j,Globals::FREE);
                        if(pred.satisfied())
                            delList.push_back(pred);
                    }
                break;
            default:
                break;
        }
        return delList;
}

list<Predicate> Action::Goals()
{
    //initialization
    int i,j,x_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().x,y_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().x,x_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().y;

    list<Predicate> goalList = list<Predicate>();

    switch (type) {
            case MOVE_RIGHT:
                for(i=x_bottomright; i>=x_topleft; i--)
                    if(theBuilding.getStatus(i,y_topleft) == objID)
                         goalList.insert(goalList.end(), Predicate(i,y_topleft,Globals::FREE));
                break;
            case MOVE_LEFT:
                for(i=x_bottomright; i>=x_topleft; i--)
                    if(theBuilding.getStatus(i,y_bottomright) == objID)
                          goalList.insert(goalList.end(), Predicate(i,y_bottomright,Globals::FREE));
                break;
            case MOVE_UP:
                for(j=y_bottomright; j>=y_topleft; j--)
                     if(theBuilding.getStatus(x_bottomright,j) == objID)
                        goalList.insert(goalList.end(), Predicate(x_bottomright,j,Globals::FREE));
                break;
            case MOVE_DOWN:
                for(j=y_bottomright; j>=y_topleft; j--)
                      if(theBuilding.getStatus(x_topleft,j) == objID)
                        goalList.insert(goalList.end(), Predicate(x_topleft,j,Globals::FREE));
                break;
            case ROTATE_LEFT:case ROTATE_RIGHT:	//rotations
                for(i=x_bottomright; i>=x_topleft; i--)
                    for(j=y_bottomright; j>=y_topleft; j--)
                        goalList.insert(goalList.end(), Predicate(i,j,Globals::FREE));

                break;
            default:
                break;
        }

        return goalList;
}

bool Action::doit()
{
    //initialization
    int i,j,x_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().x,y_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().x,x_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().y;

    switch (type) {
    case MOVE_RIGHT:
        for(i=x_topleft; i <= x_bottomright; i++)
        {
            theBuilding.setTatus(i,y_bottomright+1,objID);
            theBuilding.setTatus(i,y_topleft ,Globals::FREE);
        }
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft + 1);
        theBuilding.objectsMap[objID].setDownRightPoint(x_bottomright ,y_bottomright + 1);
            break;

    case MOVE_LEFT:
        for(i=x_topleft; i <= x_bottomright; i++)
        {
            theBuilding.setTatus(i,y_topleft-1,objID);
            theBuilding.setTatus(i,y_bottomright  ,Globals::FREE);
        }
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft - 1);
        theBuilding.objectsMap[objID].setDownRightPoint(x_bottomright ,y_bottomright - 1);
            break;
    case MOVE_UP:
        for(j = y_topleft ;j <= y_bottomright ;j++)
        {
            theBuilding.setTatus(x_topleft - 1 ,j ,objID);
            theBuilding.setTatus(x_bottomright ,j  ,Globals::FREE);
        }
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft - 1,y_topleft);
        theBuilding.objectsMap[objID].setDownRightPoint(x_bottomright -1 ,y_bottomright);
        break;
    case MOVE_DOWN:
        for(j = y_topleft ;j <= y_bottomright ;j++)
        {
            theBuilding.setTatus(x_bottomright + 1 ,j ,objID);
            theBuilding.setTatus(x_topleft ,j  ,Globals::FREE);
        }
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft + 1,y_topleft);
        theBuilding.objectsMap[objID].setDownRightPoint(x_bottomright +1 ,y_bottomright);
        break;
    case ROTATE_RIGHT:
        for(i=x_topleft; i <= x_bottomright; i++)
            for(j=y_topleft ; j <= y_bottomright; j++)
                theBuilding.setTatus(i,j  ,Globals::FREE);
        for(i=x_topleft; i <= x_topleft+y_bottomright-y_topleft; i++)
            for(j=y_topleft-1-(x_bottomright-x_topleft); j <= y_topleft-1; j++)
                theBuilding.setTatus(i,j  ,objID);
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft-1-(x_bottomright-x_topleft));
        theBuilding.objectsMap[objID].setDownRightPoint(x_topleft+y_bottomright-y_topleft, y_topleft-1);
        break;
    case ROTATE_LEFT:
        for(i=x_topleft; i <= x_bottomright; i++)
            for(j=y_topleft ; j <= y_bottomright; j++)
                theBuilding.setTatus(i,j  ,Globals::FREE);
        for(i=x_topleft-1 - (y_bottomright - y_topleft); i <= x_topleft-1; i++)
            for(j=y_topleft; j <= y_topleft+(x_bottomright - x_topleft); j++)
                theBuilding.setTatus(i,j  ,objID);
        theBuilding.objectsMap[objID].setTopLeftPoint(x_topleft-1 - (y_bottomright - y_topleft) ,y_topleft);
        theBuilding.objectsMap[objID].setDownRightPoint(x_topleft-1, y_topleft+(x_bottomright - x_topleft));
        break;
    default:
        break;
    }
    return true;
}
