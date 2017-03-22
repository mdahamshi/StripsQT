#include "functions.h"

Building &theBuilding = Broker::getInstance()->buildingBoard;
Building &theGoal = Broker::getInstance()->desiredBoard;
bool findInList(Predicate pred,list<Predicate> plist){
    list<Predicate>::iterator iter=plist.begin();
    for(; iter!=plist.end(); ++iter)
        if((*iter)==pred)
            return true;
    return false;
}

void initialize_goals(){
    Genpred goal=Genpred(ofROOM,1);
    StackNode goal_node=StackNode(GENERAL_PREDICATE);
    goal_node.gpred=Genpred(goal);
    strips.push(goal_node);
    strips.push(goal_node);
}

void Keep(list<Predicate> preds){
    list<Predicate>::iterator iter=preds.begin();
    for(; iter!=preds.end(); ++iter)
        keep_Predicates.push_back(*iter);
}

bool IsInCommon(list<Predicate> l1,list<Predicate> l2){
    list<Predicate>::iterator iter=l1.begin();
    for(; iter!=l1.end(); ++iter)
        if(findInList(*iter, l2))
           return true;
    return false;
}

int operation_rank(int h, int objID){	// Heuristic for the better operations at the moment
    //initialization
    int i,j,x_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().x,y_topleft = theBuilding.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().x,x_bottomright = theBuilding.objectsMap[objID].getDownRightPoint().y
            ,gx_topleft = theGoal.objectsMap[objID].getTopLeftPoint().x ,gy_topleft = theGoal.objectsMap[objID].getTopLeftPoint().y
            ,gx_bottomright = theGoal.objectsMap[objID].getDownRightPoint().x ,gy_bottomright = theGoal.objectsMap[objID].getDownRightPoint().y;

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
