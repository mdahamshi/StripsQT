#include "functions.h"



bool findInList(Predicate pred,list<Predicate> plist)
{
    list<Predicate>::iterator iter=plist.begin();
    for(; iter!=plist.end(); ++iter)
        if((*iter)==pred)
            return true;
    return false;
}

void initialize_goals()
{
    Genpred goal=Genpred(ofROOM,1);
    StackNode goal_node=StackNode(GENERAL_PREDICATE);
    goal_node.gpred=Genpred(goal);
    strips.push(goal_node);
    strips.push(goal_node);
    std::cout<<"in initilize goals , strips size: "<<strips.size()<<std::endl;
}

void Keep(list<Predicate> preds)
{
    list<Predicate>::iterator iter=preds.begin();
    for(; iter!=preds.end(); ++iter)
        keep_predicates.push_back(*iter);
}

bool IsInCommon(list<Predicate> l1,list<Predicate> l2)
{
    list<Predicate>::iterator iter=l1.begin();
    for(; iter!=l1.end(); ++iter)
        if(findInList(*iter, l2))
           return true;
    return false;
}
int calcHurestic(int h ,int objID ,int lastAct)
{
    Point currentTop = buildingBoard.objectsMap[objID].getTopLeftPoint() ,currentDown = buildingBoard.objectsMap[objID].getDownRightPoint()
            ,goalTop = desiredBoard.objectsMap[objID].getTopLeftPoint() ,goalDown =  desiredBoard.objectsMap[objID].getDownRightPoint();
    int currentRoam = buildingBoard.objectsMap[objID].getRoam() , goalRoam = desiredBoard.objectsMap[objID].getRoam();

}

int operation_rank(int h, int objID ,int lastAct)
{	// Heuristic for the better operations at the moment
    //initialization
    int x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x
            ,gx_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().x ,gy_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().y
            ,gx_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().x ,gy_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().y;

    int ranks[6]={1,2,3,4,5,6};	// by default, arranged like in globals.h
    bool  flag=false, flag2=false;
    if(y_topleft==gy_topleft && y_bottomright!=gy_bottomright)
        return ROTATE_LEFT;
    if(y_topleft>=gy_topleft  && y_bottomright>gy_bottomright){	// goal might be more to the left
        return MOVE_LEFT;
        }
    if(y_topleft < gy_topleft && y_bottomright < gy_bottomright)
        return MOVE_RIGHT;
    if(x_topleft < gx_topleft && x_bottomright < gx_bottomright)
        return MOVE_UP;
    if(x_topleft > gx_topleft && x_bottomright > gx_bottomright)
        return MOVE_DOWN;
    std::cout<<"WARNING*******************\n************** no move detected"<<std::endl;
    return ROTATE_RIGHT;
}

std::string gpredToString(Genpred gpred)
{
    std::string str;
        int type=gpred.type;
        switch (type) {
            case ofROOM:
                str="ALL_FURNITURES_PLACED()";
                break;
            case ofOBJECT:
                str="IN_PLACE("; str+=std::to_string(gpred.objID); str+=")";
                break;
            default:
                break;
            }
//        str += "<br/>";
        return str;
}

std::string actToString(Action act)
{
    std::string str;
        int obj = act.objID;
        switch (act.type) {
            case MOVE_RIGHT:
                str=std::string("Move_Right")+std::string("(")+std::to_string(obj)+std::string(")");
                break;
            case MOVE_LEFT:
                str="Move_Left"+std::string("(")+std::to_string(obj)+")";
                break;
            case MOVE_UP:
                str="Move_Up"+std::string("(")+std::to_string(obj)+")";
                break;
            case MOVE_DOWN:
                str="Move_Down"+std::string("(")+std::to_string(obj)+")";
                break;
            case ROTATE_RIGHT:
                str="Rotate_Right("+std::to_string(obj)+")";
                break;
            case ROTATE_LEFT:
                str="Rotate_Left("+std::to_string(obj)+")";
                break;
            default:
                break;
        }

        return str;
}

std::string predToString(Predicate pred)
{
    std::string str;
    switch(pred.objID){
        case Globals::FREE:
            str="CLEAR(["; str+=std::to_string(pred.xpos); str+=",";
            str+=std::to_string(pred.ypos);	str+="])";
            break;
        case Globals::WALL:
            str="WALL(["; str+=std::to_string(pred.xpos); str+=",";
            str+=std::to_string(pred.ypos);	str+="])";
            break;
        default:
            str="AT("; str+=std::to_string(pred.objID); str+=", [";
            str+=std::to_string(pred.xpos);	str+=","; str+=pred.ypos;
            str+="])";
            break;
    }
//    str += "<br/>";
    return str;
}
bool gpred_conj_sat(list<Genpred> conj)
{
    list<Genpred>::iterator iter=conj.begin();
        for(; iter!=conj.end(); ++iter)
            if(!(gpred_sat(*iter)))
                return false;
        return true;
}
bool gpred_sat(Genpred gpred)
{
    if (gpred.type==ofOBJECT)
        return conj_sat(gpred.conditions());
    list<Genpred> gpreds=gpred.expand();
    list<Genpred>::iterator iter=gpreds.begin();
    for(;iter!=gpreds.end(); ++iter)
        if(!gpred_sat(*iter))
            return false;
    return true;
}
bool conj_sat(list<Predicate> conj)
{
    list<Predicate>::iterator iter=conj.begin();
        for(; iter!=conj.end(); ++iter)
            if(!(iter->satisfied()))
                return false;
        return true;
}
