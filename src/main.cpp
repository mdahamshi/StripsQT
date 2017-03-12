#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "broker.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Broker::declareQML();
    engine.rootContext()->setContextProperty("myBroker",Broker::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
