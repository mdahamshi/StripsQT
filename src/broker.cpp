#include "broker.h"


Broker* Broker::m_Instance = NULL;
Broker::Broker(QObject *parent) : QObject(parent)
{

}
Broker::Broker()
{
    buildingBoard.initializeBoard();
#ifdef _MYDEB_
    buildingBoard.printBoard();
#endif

}

int Broker::getStatus(int i, int j)
{
    return buildingBoard.getStatus(i ,j);
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
    emit updateBuilding();
}
