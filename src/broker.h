#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>
#include <stack>
#include "building.h"
#include "stacknode.h"
#include <list>

//#include "functions.h"
#include <qstack.h>
#ifndef _MYDEB_
#define _MYDEB_
#endif


#include <QTime>

extern Building buildingBoard = Building();
extern Building desiredBoard = Building();
extern std::stack<StackNode> strips = std::stack<StackNode>();
extern std::list<Predicate> keep_Predicates = std::list<Predicate>();

class Broker: public  QObject
{
    Q_OBJECT

private:
    static  Broker *  m_Instance;

    int objectsNum;

public:
    Building &buildingBoard = buildingBoard;
    Building &desiredBoard = desiredBoard;
    QStack<QString> stack;
    static void declareQML() {
        qmlRegisterType<Broker>("strips", 1, 0, "Broker");
    }
    static Broker *getInstance(){
        if (! m_Instance)
            return new Broker();
        return m_Instance;
    }
    Broker();
    Broker(QObject *parent);
    Q_INVOKABLE void test(){std::cout<<"in test function";emit updateBuilding();}
    Q_INVOKABLE int getStatus(int i ,int j,int);
    Q_INVOKABLE int getBoardSize();
    Q_INVOKABLE void resetBoard();
    Q_INVOKABLE void addObject(int firstX, int firstY,int secX ,int secY,int index , int whichBoard);
    Q_INVOKABLE void copyBoard();
    Q_INVOKABLE void printBoard(){desiredBoard.printBoard();}
    Q_INVOKABLE void beginSolving();
    Q_INVOKABLE void setResetReq();
    void delay();
signals:
    void updateBuilding();
    void resetAll();
    void updateStack(QString str);

};

#endif // BROKER_H
