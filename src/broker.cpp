#include "broker.h"

bool resetRequest = false;
Broker* Broker::m_Instance = NULL;
Broker::Broker(QObject *parent) : QObject(parent)
{

}

void Broker::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
Broker::Broker()
{
    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
    objectsNum = 0;
    stack.push("hello");
    stack.push("hello2");

#ifdef _MYDEB_
    buildingBoard.printBoard();
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
    emit updateStack(QString ("Hello stack"));

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

//    resetRequest = false;
#ifdef _MYDEB_
    std::cout<<"in begin solve board ..objects: "<<objectsNum<<std::endl;
    buildingBoard.printBoard();
    desiredBoard.printBoard();

#endif
    if(resetRequest)
        return;
    std::cout<<"trying to solve..."<<std::endl;
    delay();
    return beginSolving();
}

void Broker::resetBoard()
{
    resetRequest = true;
    objectsNum = 0;
    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
#ifdef _MYDEB_
    std::cout<<"in reset board .."<<std::endl;
    buildingBoard.printBoard();
    desiredBoard.printBoard();

#endif


    emit updateBuilding();

}
