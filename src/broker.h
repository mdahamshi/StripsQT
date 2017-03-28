#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>
#include <stack>
#include "stacknode.h"
#include <list>
#include <qstring.h>
#include "globavars.h"
#include "functions.h"
#include <qstack.h>
#ifndef _MYDEB_
#define _MYDEB_
#endif


#include <QTime>



class Broker: public  QObject
{
    Q_OBJECT

private:
    static  Broker *  m_Instance;

    int objectsNum;
    int speed;
    list <Action> done_actions;
    list <Predicate> todo_predicates;
    int movingobjs[256]={0};
    Action lastact;

public:

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
    Q_INVOKABLE void togglePause();
    int solveRec();
    void DisplaySTRIPS();
    void delay(int);
    int getSpeed() const;
    void setSpeed(int value);

signals:
    void updateBuilding();
    void resetAll();
    void updateStack(QString str);
    void solved();
    void updateState(std::string msg);
    void noSol();
    void updateCurrent();


};

#endif // BROKER_H
