#include "action.h"
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
    int i,j,x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x;
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
        std::cout<<"PRE COND for : ";buildingBoard.objectsMap[objID].print();
        for(j=y_topleft; j <= y_bottomright; j++){
            reqPreCond.insert(reqPreCond.end(),Predicate(x_bottomright + 1 , j, Globals::FREE));
            std::cout<<"MOVE_DOWN PRE COND: clear "<<x_bottomright+1<<","<<j<<std::endl;
        }


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
    int i,j,x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x;

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
    int i,j,x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x;

    list<Predicate> goalList = list<Predicate>();

    switch (type) {
            case MOVE_RIGHT:
                for(i=x_bottomright; i>=x_topleft; i--)
                    if(buildingBoard.getStatus(i,y_topleft) == objID)
                         goalList.insert(goalList.end(), Predicate(i,y_topleft,Globals::FREE));
                break;
            case MOVE_LEFT:
                for(i=x_bottomright; i>=x_topleft; i--)
                    if(buildingBoard.getStatus(i,y_bottomright) == objID)
                          goalList.insert(goalList.end(), Predicate(i,y_bottomright,Globals::FREE));
                break;
            case MOVE_UP:
                for(j=y_bottomright; j>=y_topleft; j--)
                     if(buildingBoard.getStatus(x_bottomright,j) == objID)
                        goalList.insert(goalList.end(), Predicate(x_bottomright,j,Globals::FREE));
                break;
            case MOVE_DOWN:
                for(j=y_bottomright; j>=y_topleft; j--)
                      if(buildingBoard.getStatus(x_topleft,j) == objID)
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
    int i,j,x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x;

    switch (type) {
    case MOVE_RIGHT:
        for(i=x_topleft; i <= x_bottomright; i++)
        {
            buildingBoard.setTatus(i,y_bottomright+1,objID);
            buildingBoard.setTatus(i,y_topleft ,Globals::FREE);
        }
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft + 1);
        buildingBoard.objectsMap[objID].setDownRightPoint(x_bottomright ,y_bottomright + 1);
            break;

    case MOVE_LEFT:
        for(i=x_topleft; i <= x_bottomright; i++)
        {
            buildingBoard.setTatus(i,y_topleft-1,objID);
            buildingBoard.setTatus(i,y_bottomright  ,Globals::FREE);
        }
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft - 1);
        buildingBoard.objectsMap[objID].setDownRightPoint(x_bottomright ,y_bottomright - 1);
            break;
    case MOVE_UP:
        for(j = y_topleft ;j <= y_bottomright ;j++)
        {
            buildingBoard.setTatus(x_topleft - 1 ,j ,objID);
            buildingBoard.setTatus(x_bottomright ,j  ,Globals::FREE);
        }
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft - 1,y_topleft);
        buildingBoard.objectsMap[objID].setDownRightPoint(x_bottomright -1 ,y_bottomright);
        break;
    case MOVE_DOWN:
        for(j = y_topleft ;j <= y_bottomright ;j++)
        {
            buildingBoard.setTatus(x_bottomright + 1 ,j ,objID);
            buildingBoard.setTatus(x_topleft ,j  ,Globals::FREE);
        }
        std::cout<<"moved down: ";buildingBoard.objectsMap[objID].print();
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft + 1,y_topleft);
        buildingBoard.objectsMap[objID].setDownRightPoint(x_bottomright +1 ,y_bottomright);
        std::cout<<"new cor: ";buildingBoard.objectsMap[objID].print();
        break;
    case ROTATE_RIGHT:
        for(i=x_topleft; i <= x_bottomright; i++)
            for(j=y_topleft ; j <= y_bottomright; j++)
                buildingBoard.setTatus(i,j  ,Globals::FREE);
        for(i=x_topleft; i <= x_topleft+y_bottomright-y_topleft; i++)
            for(j=y_topleft-1-(x_bottomright-x_topleft); j <= y_topleft-1; j++)
                buildingBoard.setTatus(i,j  ,objID);
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft ,y_topleft-1-(x_bottomright-x_topleft));
        buildingBoard.objectsMap[objID].setDownRightPoint(x_topleft+y_bottomright-y_topleft, y_topleft-1);
        break;
    case ROTATE_LEFT:
        for(i=x_topleft; i <= x_bottomright; i++)
            for(j=y_topleft ; j <= y_bottomright; j++)
                buildingBoard.setTatus(i,j  ,Globals::FREE);
        for(i=x_topleft-1 - (y_bottomright - y_topleft); i <= x_topleft-1; i++)
            for(j=y_topleft; j <= y_topleft+(x_bottomright - x_topleft); j++)
                buildingBoard.setTatus(i,j  ,objID);
        buildingBoard.objectsMap[objID].setTopLeftPoint(x_topleft-1 - (y_bottomright - y_topleft) ,y_topleft);
        buildingBoard.objectsMap[objID].setDownRightPoint(x_topleft-1, y_topleft+(x_bottomright - x_topleft));
        break;
    default:
        break;
    }

    return true;
}
