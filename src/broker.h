#ifndef BROKER_H
#define BROKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlEngine>
#include "globals.h"
#include "building.h"
#ifndef _MYDEB_
#define _MYDEB_
#endif
class Broker: public  QObject
{
    Q_OBJECT

private:
    static  Broker *  m_Instance;
    Building buildingBoard;

public:

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
    Q_INVOKABLE int getStatus(int i ,int j);
    Q_INVOKABLE int getBoardSize();
    Q_INVOKABLE void resetBoard();
signals:
    void updateBuilding();

};

#endif // BROKER_H
