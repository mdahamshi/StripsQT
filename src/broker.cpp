#include "broker.h"


Broker* Broker::m_Instance = NULL;
Broker::Broker(QObject *parent) : QObject(parent)
{

}
Broker::Broker()
{
    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
#ifdef _MYDEB_
    buildingBoard.printBoard();
#endif

}
void Broker::addObject(int firstX, int firstY,int secX ,int secY ,int index,int whichBoard)
{
    if(whichBoard == Globals::CURRENT_BOARD)
        buildingBoard.addObject(firstX,  firstY, secX , secY ,index);
    else
        desiredBoard.addObject(firstX,  firstY, secX , secY ,index);

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
void Broker::resetBoard()
{
#ifdef _MYDEB_
    std::cout<<"in reset board .."<<std::endl;
#endif
    buildingBoard.initializeBoard();
    desiredBoard.initializeBoard();
    emit updateBuilding();
}
