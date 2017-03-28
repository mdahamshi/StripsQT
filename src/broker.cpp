#include "broker.h"

bool resetRequest = false;
bool pause = false;
Building buildingBoard = Building();
Building desiredBoard = Building();
std::stack<StackNode> strips = std::stack<StackNode>() ;
std::list<Predicate> keep_predicates = std::list<Predicate>();
bool foundWall = false;
bool disablFir = false;

Broker* Broker::m_Instance = NULL;
Broker::Broker(QObject *parent) : QObject(parent)
{

}

void Broker::delay(int speed=2)
{
    QTime dieTime= QTime::currentTime().addMSecs(speed);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
int Broker::getSpeed() const
{
    return speed;
}

void Broker::setSpeed(int value)
{
    speed = value;
}

void Broker::togglePause()
{
    pause = ! pause;
}

Broker::Broker()
{

    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
    speed = 1;
    objectsNum = 0;
    stack.push("hello");
    stack.push("hello2");

#ifdef _MYDEB_
//    buildingBoard.printBoard();
#endif

}
void Broker::addObject(int firstX, int firstY,int secX ,int secY ,int index,int whichBoard)
{

    if(whichBoard == Globals::CURRENT_BOARD)
    {
        buildingBoard.addObject(firstX,  firstY, secX , secY ,index);
        objectsNum++;
    }
    else
        desiredBoard.addObject(firstX,  firstY, secX , secY ,index);

}
void Broker::setResetReq()
{
    resetRequest = true;
}

void Broker::copyBoard()
{
    for(int i=1 ;i < TOTAL_HEIGHT - 1 ;i++)
        for(int j=1 ;j < TOTAL_WIDTH - 1 ;j++)
            desiredBoard.board[i][j] = buildingBoard.board[i][j];
    emit updateBuilding();
}

int Broker::getStatus(int i, int j ,int whichBoard)
{
    return whichBoard == Globals::CURRENT_BOARD ? buildingBoard.getStatus(i ,j) : desiredBoard.getStatus(i,j);
}
int Broker::getBoardSize()
{
    return buildingBoard.getBoardSize();
}
void Broker::beginSolving()
{

    resetRequest = false;
      QCoreApplication::processEvents();
      initialize_goals();
      int solveRes = solveRec();
      if(solveRes == Globals::SOLVED)
          emit solved();
      else if (solveRes == Globals::NOSOL){
          emit noSol();
      }
#ifdef _MYDEB_
    std::cout<<"in begin solve board ..objects: "<<buildingBoard.getObjectNum()<<std::endl;
    std::cout<<"last status : current then desired:"<<std::endl;
    buildingBoard.printBoard();
    desiredBoard.printBoard();

#endif


}

void Broker::resetBoard()
{
    resetRequest = true;
    objectsNum = 0;
    pause = false;
    disablFir = false;
    strips = std::stack<StackNode>();
    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
#ifdef _MYDEB_
    std::cout<<"in reset board .."<<std::endl;
    buildingBoard.printBoard();
    desiredBoard.printBoard();

#endif


    emit updateBuilding();

}

int  Broker::solveRec()
{
    QCoreApplication::processEvents();
    if(resetRequest)
        return Globals::RESET;
    if(pause)
        while (pause) {
            delay(100);
        }
    DisplaySTRIPS();
        delay(20*speed);
        StackNode ontop, next;
        Action act;
        Building tempboard;
        list<Predicate> conj, tempkeeppreds=keep_predicates;
        list<Genpred> genpredconj;
        Genpred genpred;
        bool trySec = false,firstHur = false;
        std::stack<StackNode> tempstack=std::stack<StackNode>(strips);
        static int shuffleflag=0;	// pilot. not used.
        int i2,j2,k2,notonobj=0,i;
        // save the board for backtracking purposes

        tempboard = Building(buildingBoard);

        Predicate pred;
        if(strips.empty()){	// stack is empty... Good!
            DisplaySTRIPS();
            return true;
        }	// not empty.
        ontop=StackNode(strips.top());	// the element on top of the stack
        strips.pop();	// remove it.
        tempstack.pop();
        switch (ontop.type) {	// switch on the type of the element
            case GENERAL_PREDICATE_CONJUNCTION:{	// a conjunction of general elements.
                genpredconj=ontop.gpredconj;
                if(gpred_conj_sat(genpredconj)){
                    // all the general predicates in the conj. are satisfied, good!
                    return solveRec();
                }
                strips.push(ontop);	// not satisfied, push it back.
                list<Genpred>::iterator iter=genpredconj.begin();
                for (; iter!=genpredconj.end(); ++iter) {	// push all general predicates in the conj.
                    next=StackNode(GENERAL_PREDICATE);
                    next.gpred=*iter;
                    strips.push(next);
                }
                return solveRec();	// solve them one by one...
                break;
            }
            case GENERAL_PREDICATE:	// a general predicate
                genpred=ontop.gpred;
                if(gpred_sat(genpred))	// satisfied, Good!
                    return solveRec();
                strips.push(ontop);	// not good, push back.
                if(genpred.type==ofROOM){	// expand the general predicate
                    next=StackNode(GENERAL_PREDICATE_CONJUNCTION);
                    next.gpredconj=genpred.expand(); // to a conj of simpler general predicates
                    strips.push(next);	// and push them
                    DisplaySTRIPS();
                    return solveRec();
                }
                next=StackNode(CONJUNCTION); // the general predicate can be expanded to single predicates
                next.conj=genpred.conditions(); // expand to a conj.
                strips.push(next); // push it
                return solveRec();
                break;
            case SINGLE_PREDICATE:{	// a simple single predicate
                pred=Predicate(ontop.pred);
                if (pred.satisfied())	// satisfied, good!
                    return solveRec();
                if(findInList(pred,todo_predicates)){	// if not satisfied but is already being handled
                    disablFir = false;
                    return false;	// Bad, we're in a loop. stop, go back and try something else.
                }
                todo_predicates.insert(todo_predicates.end(), pred); // now handling this predicate.
                int a=buildingBoard.getStatus(pred.xpos,pred.ypos);	// a is the object at the position we need to clear.
                if(a==Globals::WALL)
                    return Globals::NOSOL;	// can't clear walls.
                firstHur = true;
                for(int h=1; h<7; h++,notonobj=-1){	// try each of 6 operators/actions

                    i = firstHurestic(a);
                    if(i && !disablFir ){
                            // i is the most suitable, still-untried, operation
                        firstHur = true;

                        h=7;
                        std::cout<<"got action: "<<i<<" from first her ";buildingBoard.objectsMap[a].print();std::cout<<std::endl;

                    }
                    else
                    {
                        firstHur = false;
                        disablFir = true;

                        i=operation_rank(h,a);
                        std::cout<<"got action: "<<i<<" from sec her ";buildingBoard.objectsMap[a].print();std::cout<<std::endl;

                    }



                    if(!done_actions.empty()){
                        list<Action>::iterator acts=done_actions.end();
                        acts--;
                        if((*acts).type==7-i && !firstHur )	// last done action was the opposite of this action
                            notonobj=acts->objID;	// then don't do the operation on the same object
                    }
                    for(int k=1; k<2; k++) {	// k is the number of steps for the operation
                            if(a==notonobj || movingobjs[a]==1){	// can't move this object
                                k=8;	// stop loop
                                continue;
                            }
                            if(i==ROTATE_RIGHT || i==ROTATE_LEFT)
                                k=8;	// no steps in rotations.
                            act=Action(i,a,k);	// act is the chosen operation
                            list<Predicate> goals=act.Goals();
                            if(findInList(pred, goals) || firstHur){	// the action causes the desired predicate
                                if(IsInCommon(act.Deletions(), keep_predicates))
                                    continue;	// delets a desired predicate
                                movingobjs[a]=1;	// note this object is being moved, don't move it by another op.
                                next=StackNode(ACTION);
                                next.action=Action(act);
                                strips.push(next);	// push the op. under its reconditions
                                DisplaySTRIPS();
                                delay(20*speed);
                                next=StackNode(CONJUNCTION);
                                list<Predicate> preconds=act.PreConditions();
                                next.conj=preconds;
                                Keep(preconds);
                                strips.push(next);	// push preconditions of op.
                                DisplaySTRIPS();
                                delay(20*speed);
                                if(solveRec()){	// try to execute the operation.
                                    todo_predicates.remove(pred);	// not todo anymore
                                    keep_predicates=tempkeeppreds;	// restore
                                    movingobjs[a]=0;	// not moving a
                                    return solveRec();	// continue popping...
                                }
                                else {	// operation failed
                                    keep_predicates=tempkeeppreds;	//restore
                                    // couldn't complete operation... backtracking.
                                    strips=tempstack;	// restore board and stack.
                                    DisplaySTRIPS();
                                    delay(20*speed);
                                    // copy board

                                    buildingBoard = Building(tempboard);
                                    k=8;	// if couldn't move k steps, you can't move >k steps.
                                    if(act.type==ROTATE_RIGHT){	// try a combination.
                                        k2=1;	// move k2 steps up then rotate right!
                                        do{
                                            disablFir = true;
                                            strips=tempstack;	// restore board and stack.
                                            DisplaySTRIPS();
                                            delay(20*speed);
                                            // copy board

                                            buildingBoard = Building(tempboard);
                                            keep_predicates=tempkeeppreds;
                                            act=Action(MOVE_UP,a,k2);
                                            next=StackNode(ACTION);
                                            next.action=Action(act);
                                            strips.push(next);
                                            DisplaySTRIPS();
                                            delay(20*speed);
                                            next=StackNode(CONJUNCTION);
                                            list<Predicate> preconds=act.PreConditions();
                                            next.conj=preconds;
                                            Keep(preconds);
                                            strips.push(next);
                                            DisplaySTRIPS();
                                            delay(20*speed);
                                            if(solveRec()){	// move_up_k2 succeeded
                                                keep_predicates=tempkeeppreds;
                                                act=Action(ROTATE_RIGHT,a,1);
                                                next=StackNode(ACTION);
                                                next.action=Action(act);
                                                strips.push(next);
                                                DisplaySTRIPS();
                                                delay(20*speed);
                                                next=StackNode(CONJUNCTION);
                                                list<Predicate> preconds=act.PreConditions();
                                                next.conj=preconds;
                                                Keep(preconds);
                                                strips.push(next);
                                                DisplaySTRIPS();
                                                delay(20*speed);
                                            }
                                            else	// move_up failed, stop do-while loop
                                                k2=8;
                                            k2++;	// try moving more up
                                        }while(!solveRec() && k2<8);	// try rotating now
                                        if(k2<8){	// rotation succeeded, good.
                                            keep_predicates=tempkeeppreds;	// restore and continue
                                            todo_predicates.remove(pred);
                                            movingobjs[a]=0;
                                            return solveRec();
                                        }	// even the combination failed
                                        strips=tempstack;	// restore board and stack.
                                        DisplaySTRIPS();
                                        buildingBoard = Building(tempboard);
                                        emit updateCurrent();
                                        emit updateState("Rotation failed, restoring board");
                                        delay(1000*speed);
                                        // copy array


                                        keep_predicates=tempkeeppreds;
                                    }
                                }
                                // couldn't complete operation... backtracking.
                                strips=tempstack;	// restore board and stack.
                                DisplaySTRIPS();
                                delay(20*speed);
                                // copy array
                                buildingBoard = Building(tempboard);
                                k=8;	// if couldn't move k steps, you can't move >k steps.
                            }
                            movingobjs[a]=0;	// not moving it anymore
                    }
                }
                todo_predicates.remove(pred);	// not todo anymore
                break;
            }
            case CONJUNCTION:{	// a conjunction of single simple predicates
                conj=ontop.conj;
                if(conj_sat(conj))	// all predicate in conj. satisfied, Good!
                    return solveRec();
                strips.push(ontop);	// not satisfied, push back.
                DisplaySTRIPS();
                delay(40*speed);
                list<Predicate>::iterator iter;
                if(shuffleflag<=3)	// pilot. not used.
                    for(iter=conj.begin(); iter!=conj.end(); ++iter){ // push all predicates
                        next=StackNode(SINGLE_PREDICATE);	// in the conjunction
                        next.pred=*iter;		// to the stack and solve one by one
                        strips.push(next);
                        DisplaySTRIPS();
                        delay(20*speed);
                    }
                else // pilot. never reached.
                    for(iter=conj.end(), shuffleflag=0; iter!=conj.begin();){
                        --iter;
                        next=StackNode(SINGLE_PREDICATE);
                        next.pred=*iter;
                        strips.push(next);
                        DisplaySTRIPS();
                        delay(20*speed);
                    }
        //		shuffleflag++;
                return solveRec();
            }
            case ACTION:	// an operation/action
                act=ontop.action;
                lastact=act;	// update last action
                if(act.doit())
                    emit updateCurrent();
                        // perform it!
                done_actions.insert(done_actions.end(), act);	// update
                strips.push(ontop);	// push and pop just for the stack display.
                DisplaySTRIPS();
                strips.pop();
                delay(40*speed);
                return Globals::SOLVED;	// operation succeeded, good.
            default:
                break;
        }
        return Globals::NOSOL;
}
void Broker::DisplaySTRIPS()
{
    std::stack<StackNode> tempstack2=std::stack<StackNode>(strips);
        StackNode ontop;
        std::string str;


        while(!tempstack2.empty()){
            ontop=StackNode(tempstack2.top());
            tempstack2.pop();
            switch (ontop.type) {
                case GENERAL_PREDICATE_CONJUNCTION:{
                    list<Genpred>::iterator iter=ontop.gpredconj.begin();
                    str += gpredToString(*iter);
                    for(++iter; iter!=ontop.gpredconj.end(); ++iter){

                        str+=" & ";
                        str+=gpredToString(*iter);

                    }
                    break;
                }
                case GENERAL_PREDICATE:
                    str += gpredToString(ontop.gpred);
                    break;
                case SINGLE_PREDICATE:{
                    str += predToString(ontop.pred);
                    break;
                }
                case CONJUNCTION:{
                    list<Predicate>::iterator iter=ontop.conj.begin();
                    str += predToString(*iter);
                    if(ontop.conj.size() == 1)
                        break;
                    for(; iter!=ontop.conj.end(); ++iter){
                        str+=" & ";
                        str+=predToString(*iter);

                    }
                    break;
                }
                case ACTION:
                    str += actToString(ontop.action);
                    break;
                default:
                    break;
            }
            str+=" <br>----------------<br> ";
        }

        str += "<br/>--------------------------<br>";
        str += "*STACK FIRST CELL*<br/><br/><br/>";
#ifdef _MYDEB_
//                                    std::cout<<"----------------------"<<std::endl;
//                                    std::cout<<str<<std::endl;
#endif
        updateStack(QString::fromStdString(str));
//        updateCurrent();
}
