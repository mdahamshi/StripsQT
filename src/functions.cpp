#include "functions.h"



bool findInList(Predicate pred,list<Predicate> plist)
{
    list<Predicate>::iterator iter=plist.begin();
    for(; iter!=plist.end(); ++iter){
        if((*iter)==pred)
            return true;
        //std::cout<<"pred: ";
        //pred.print();std::cout<<std::endl;
        //std::cout<<"goal: ";
        //(*iter).print();std::cout<<std::endl;
    }
    return false;
}

void initialize_goals()
{
    Genpred goal=Genpred(ofROOM,1);
    StackNode goal_node=StackNode(GENERAL_PREDICATE);
    goal_node.gpred=Genpred(goal);
    strips.push(goal_node);
    strips.push(goal_node);
    //std::cout<<"in initilize goals , strips size: "<<strips.size()<<std::endl;
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


int operation_rank(int h, int objID )
{	// Heuristic for the better operations at the moment
    //initialization
    int x_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().x,y_topleft = buildingBoard.objectsMap[objID].getTopLeftPoint().y
            ,y_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().y,x_bottomright = buildingBoard.objectsMap[objID].getDownRightPoint().x
            ,gx_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().x ,gy_topleft = desiredBoard.objectsMap[objID].getTopLeftPoint().y
            ,gx_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().x ,gy_bottomright = desiredBoard.objectsMap[objID].getDownRightPoint().y;
    Furniture object = Furniture(buildingBoard.objectsMap[objID]);

    int ranks[6]={1,2,3,4,5,6};	// by default, arranged like in globals.h
    bool  flag=false, flag2=false;
    int objAtDoor = buildingBoard.objectAtDoor(objID) ,desiredRoam = desiredBoard.objectsMap[objID].getRoam()
            ,currentRoam = buildingBoard.objectsMap[objID].getRoam(), desiredAtDoor = desiredBoard.objectAtDoor(objID);


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
int firstHurestic(int objID)
{
    //initialization

    Furniture object = Furniture(buildingBoard.objectsMap[objID]);
    Furniture goal = Furniture(desiredBoard.objectsMap[objID]);


    bool  flag=false, flag2=false;
    int objAtDoor = buildingBoard.objectAtDoor(objID) ,desiredRoam = desiredBoard.objectsMap[objID].getRoam()
            ,currentRoam = buildingBoard.objectsMap[objID].getRoam(), desiredAtDoor = desiredBoard.objectAtDoor(objID);
    if(objAtDoor)
    {
        //std::cout<<"object at door: "<<objAtDoor;object.print();std::cout<<std::endl;
        switch (objAtDoor) {
        case FIRST_DOOR:
            if(desiredRoam == FIRST_ROAM && buildingBoard.clear(object,MOVE_UP) && object.getLastAct() != minusAct(MOVE_UP))
                return MOVE_UP;
            if(buildingBoard.clear(object,MOVE_DOWN) && object.getLastAct() != minusAct(MOVE_DOWN))
                return MOVE_DOWN;
            break;
        case SECOND_DOOR:
            if(desiredRoam == FIRST_ROAM && buildingBoard.clear(object,MOVE_LEFT) && object.getLastAct() != minusAct(MOVE_LEFT))
                return MOVE_LEFT;
            if(buildingBoard.clear(object,MOVE_RIGHT) && object.getLastAct() != minusAct(MOVE_RIGHT))
                return MOVE_RIGHT;
        case THIRD_DOOR:
            if(desiredRoam == SECOND_ROAM && buildingBoard.clear(object,MOVE_LEFT) && object.getLastAct() != minusAct(MOVE_LEFT))
                return MOVE_LEFT;
            if(buildingBoard.clear(object,MOVE_RIGHT) && object.getLastAct() != minusAct(MOVE_RIGHT))
                return MOVE_RIGHT;
        default:
            break;
        }
    }

    if(currentRoam != desiredRoam)
    {
        switch (currentRoam ) {
        case FIRST_ROAM:
            if(desiredRoam == SECOND_ROAM)
            {
                if(moveThroughFirstDoor(object,SECOND_ROAM))
                    return moveThroughFirstDoor(object,SECOND_ROAM);
                if(moveThroughSecondDoor(object,THIRD_ROAM))
                    return moveThroughSecondDoor(object,THIRD_ROAM);
                else{
                    flag =true;
                    flag2 = true;
                }
            }
            if(desiredRoam == THIRD_ROAM)
            {
                if(moveThroughSecondDoor(object,THIRD_ROAM)){
                    return moveThroughSecondDoor(object,THIRD_ROAM);
                }
                else if(moveThroughFirstDoor(object,SECOND_ROAM))
                    return moveThroughFirstDoor(object,SECOND_ROAM);
                else{
                    flag =true;
                    flag2 = true;
                }
            }

            break;
        case SECOND_ROAM:
            //std::cout<<"in second roam "<<std::endl;
            if(desiredRoam == FIRST_ROAM)
            {
                if(moveThroughFirstDoor(object,FIRST_ROAM))
                    return moveThroughFirstDoor(object,FIRST_ROAM);
                else if(moveThroughThirdDoor(object,THIRD_ROAM) && object.getHeight() <= Building::secondDoor.getSize())
                    return moveThroughThirdDoor(object,THIRD_ROAM);
            }
            //std::cout<<"in second roam des = 3 "<<std::endl;
            if(desiredRoam == THIRD_ROAM)
            {   if(moveThroughThirdDoor(object,THIRD_ROAM))
                    return moveThroughThirdDoor(object,THIRD_ROAM);
                if(moveThroughFirstDoor(object,FIRST_ROAM))
                    return moveThroughFirstDoor(object,FIRST_ROAM);
                else{
                    flag =true;
                    flag2 = true;
                }
            }
            break;
        case THIRD_ROAM:
            //std::cout<<"in third roam "<<std::endl;
            if(desiredRoam == FIRST_ROAM)
            {
                if(moveThroughSecondDoor(object,FIRST_ROAM)){
                    //std::cout<<"trying move through second door..."<<std::endl;
                    return moveThroughSecondDoor(object,FIRST_ROAM);
                }
                else if (moveThroughThirdDoor(object,SECOND_ROAM))
                        return moveThroughThirdDoor(object,SECOND_ROAM);
                else{
                    flag =true;
                    flag2 = true;
                }
            }
            //std::cout<<"in third roam des = 2 "<<std::endl;
            if(desiredRoam == SECOND_ROAM)
            {
                if(moveThroughThirdDoor(object,SECOND_ROAM))
                    return moveThroughThirdDoor(object,SECOND_ROAM);
                if(moveThroughSecondDoor(object,SECOND_ROAM))
                    return moveThroughSecondDoor(object,SECOND_ROAM);
                else{
                    flag =true;
                    flag2 = true;
                }
            }
        default:
            break;
        }
    }
    else
    {
        //std::cout<<"in first hurostic nirmal"<<std::endl;
        if(object.getWidth() != goal.getWidth())
            return Globals::NOSOL;
        if(object.getTopLeftPoint().y >= goal.getTopLeftPoint().y && object.getDownRightPoint().y > goal.getDownRightPoint().y)	// goal might be more to the left
            if(buildingBoard.clear(object,MOVE_LEFT) && object.getLastAct() != minusAct(MOVE_LEFT))
                return MOVE_LEFT;
        if(object.getTopLeftPoint().y <= goal.getTopLeftPoint().y && object.getDownRightPoint().y < goal.getDownRightPoint().y)
            if(buildingBoard.clear(object,MOVE_RIGHT) && object.getLastAct() != minusAct(MOVE_RIGHT))
                return MOVE_RIGHT;
        if(object.getTopLeftPoint().x >= goal.getTopLeftPoint().x && object.getDownRightPoint().x > goal.getDownRightPoint().x)	// goal might be more upwards
            if(buildingBoard.clear(object,MOVE_UP) && object.getLastAct() != minusAct(MOVE_UP))
                return MOVE_UP;
        if(object.getTopLeftPoint().x <= goal.getTopLeftPoint().x && object.getDownRightPoint().x < goal.getDownRightPoint().x)
            if(buildingBoard.clear(object,MOVE_DOWN) && object.getLastAct() != minusAct(MOVE_DOWN))
                return MOVE_DOWN;
    }
    return Globals::NOSOL;
}

int getDoorDir(int door)
{
    if(door == FIRST_DOOR)
        return Globals::HOR;
    return Globals::VER;
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
int minusAct(int act)
{
    return 7 - act;
}

int moveThroughFirstDoor(Furniture object ,int desired)
{

    //std::cout<<"in move through first door"<<std::endl;
    if(buildingBoard.doorIsClear(FIRST_DOOR) == false || object.getWidth() > Building::firstDoor.getSize())
        return Globals::NOSOL;
    if(desiredBoard.objectsMap[object.getId()].getRoam() == THIRD_ROAM && object.getHeight() > Building::secondDoor.getSize())
        return Globals::NOSOL;
    if(object.getWidth() > Building::firstDoor.getSize())
    {
        if(object.getHeight() <= Building::secondDoor.getSize())
            return moveThroughSecondDoor(object,THIRD_ROAM);
        if(object.getHeight() <= Building::firstDoor.getSize())
            return Globals::NOSOL;
    }
    if(object.getTopLeftPoint().y < Building::firstDoor.getTopLeftPoint().y)
        if(buildingBoard.clear(object,MOVE_RIGHT)  && object.getLastAct() != minusAct(MOVE_RIGHT))
            return MOVE_RIGHT;
    if(object.getDownRightPoint().y > Building::firstDoor.getDownRightPoint().y)
        if(buildingBoard.clear(object,MOVE_LEFT) && object.getLastAct() != minusAct(MOVE_LEFT))
              return MOVE_LEFT;
    if(desired == SECOND_ROAM){
        if(buildingBoard.clear(object,MOVE_DOWN) && object.getLastAct() != minusAct(MOVE_DOWN))
             return MOVE_DOWN;
    }
    else if(buildingBoard.clear(object,MOVE_UP) && object.getLastAct() != minusAct(MOVE_UP))
        return MOVE_UP;
    //std::cout<<"move t 1 returned no "<<std::endl;
    return Globals::NOSOL;
}
int moveThroughThirdDoor(Furniture object ,int desired)
{
    if(buildingBoard.doorIsClear(THIRD_DOOR) == false || object.getHeight() > Building::thirdDoor.getSize())
        return Globals::NOSOL;
    //std::cout<<"in move through third door"<<std::endl;
    if(object.getHeight() > Building::thirdDoor.getSize())
    {
        if(object.getWidth() <= Building::thirdDoor.getSize())
            return Globals::NOSOL;
    }
    if(object.getTopLeftPoint().x < Building::thirdDoor.getTopLeftPoint().x)
        if(buildingBoard.clear(object,MOVE_DOWN) && object.getLastAct() != minusAct(MOVE_DOWN))
            return MOVE_DOWN;
    if(object.getDownRightPoint().x > Building::thirdDoor.getDownRightPoint().x)
        if(buildingBoard.clear(object,MOVE_UP) && object.getLastAct() != minusAct(MOVE_UP))
            return MOVE_UP;
    if(desired == THIRD_ROAM){
        if(buildingBoard.clear(object,MOVE_RIGHT) && object.getLastAct() != minusAct(MOVE_RIGHT))
              return MOVE_RIGHT;
    }
    else if(buildingBoard.clear(object,MOVE_LEFT)&& object.getLastAct() != minusAct(MOVE_LEFT))
          return MOVE_LEFT;
    //std::cout<<"move t 3 returned no "<<std::endl;
    return Globals::NOSOL;
}

int moveThroughSecondDoor(Furniture object ,int desired)
{
    if(buildingBoard.doorIsClear(SECOND_DOOR) == false || object.getHeight() > Building::secondDoor.getSize())
        return Globals::NOSOL;
    //std::cout<<"in move through second door"<<std::endl;
    if(object.getHeight() > Building::secondDoor.getSize())
    {
        //std::cout<<"fuck height is big"<<std::endl;
        if(object.getWidth() <= Building::secondDoor.getSize())
            return Globals::NOSOL;
    }

        if(object.getTopLeftPoint().x < Building::secondDoor.getTopLeftPoint().x){
            if(buildingBoard.clear(object,MOVE_DOWN) && object.getLastAct() != minusAct(MOVE_DOWN))
                return MOVE_DOWN;
        }
        if(object.getDownRightPoint().x > Building::secondDoor.getDownRightPoint().x){
             if(buildingBoard.clear(object,MOVE_UP) && object.getLastAct() != minusAct(MOVE_UP))
                return MOVE_UP;
             //else std::cout<<"not clear to move up !";
        }
        if(desired == THIRD_ROAM){
            if(buildingBoard.clear(object,MOVE_RIGHT) && object.getLastAct() != minusAct(MOVE_RIGHT))
                return MOVE_RIGHT;
        }
        else if(buildingBoard.clear(object,MOVE_LEFT) && object.getLastAct() != minusAct(MOVE_LEFT))
             return MOVE_LEFT;



        //std::cout<<"move t 2 returnod no !"<<std::endl;
        return Globals::NOSOL;
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
