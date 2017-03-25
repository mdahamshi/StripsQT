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

int operation_rank(int h, int objID)
{	// Heuristic for the better operations at the moment
    //initialization
    int x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x
            ,gx_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().x ,gy_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().y
            ,gx_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().x ,gy_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().y;

    int ranks[6]={1,2,3,4,5,6};	// by default, arranged like in globals.h
    bool  flag=false, flag2=false;

    if(y_topleft==gy_topleft && y_bottomright!=gy_bottomright){	// needs rotation
        ranks[0]=ROTATE_RIGHT;	ranks[1]=ROTATE_LEFT;	// re-arrange the operations
        ranks[2]=MOVE_RIGHT; ranks[3]=MOVE_DOWN;	// rotations better than moves
    }
    else{
        if(y_topleft>=gy_topleft){	// goal might be more to the left
            if(y_bottomright>gy_bottomright){ // goal is more to the left
                ranks[0]=MOVE_LEFT;	ranks[5]=MOVE_RIGHT;	// swap right/left
                flag=true;
            }
            else{	// needs rotation, re-arrange to prefer it
                ranks[0]=MOVE_DOWN;	ranks[5]=MOVE_UP;
                ranks[1]=ROTATE_RIGHT;	ranks[4]=ROTATE_LEFT;
                ranks[2]=MOVE_RIGHT; ranks[3]=MOVE_LEFT;
                flag=true;
                flag2=true;
            }
        }
        if(x_topleft>=gx_topleft){	// goal might be more upwards
            if(x_bottomright>gx_bottomright){	// goal is more upwards
                if(flag&&flag2){
                    ranks[0]=MOVE_UP;	ranks[5]=MOVE_DOWN;	//swap up/down
                }
                else {
                    ranks[1]=MOVE_UP;	ranks[4]=MOVE_DOWN;	//swap up/down
                }
            }
            else{	// needs rotation, rearrange to prefer it
                if(flag){
                    ranks[1]=ranks[0];	ranks[4]=ranks[5];
                    ranks[0]=ROTATE_RIGHT;	ranks[5]=ROTATE_LEFT;
                }
                else{
                    if(x_topleft!=gx_topleft && x_bottomright!=gx_bottomright){
                        ranks[1]=ROTATE_RIGHT;	ranks[4]=ROTATE_LEFT;
                        ranks[2]=MOVE_DOWN; ranks[3]=MOVE_UP;
                    }
                }
            }
        }
    }
    return ranks[h-1];
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
