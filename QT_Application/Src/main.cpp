#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFontDatabase>
#include <QDebug>

#include "ScreenHelper.h"
#include "mynetwork.h"
#include "sensorlist.h"
#include "sensormodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    //QFontDatabase::addApplicationFont(QString::fromLatin1(":/Lato-Light.ttf"));
    //app.setFont(QFont("Lato Light", 20));

    qmlRegisterType<SensorModel>("Sensor", 1, 0, "SensorModel");
    qmlRegisterUncreatableType<SensorList>("Sensor", 1, 0, "SensorList",
        QStringLiteral("SensorList should not be created in QML"));



    QQmlApplicationEngine engine;

    ScreenHelper screenHelper;
    engine.rootContext()->setContextProperty("SH", &screenHelper);

    SensorModel sensorModel;
    engine.rootContext()->setContextProperty(QStringLiteral("sensorModel"), &sensorModel);

    SensorList sensorList;
    engine.rootContext()->setContextProperty(QStringLiteral("sensorList"), &sensorList);

    sensorModel.setList(&sensorList);
    sensorModel.setList(&sensorList);

    MyNetwork myNetwork(nullptr, &sensorModel) ;
    engine.rootContext()->setContextProperty("myNetwork", &myNetwork);



    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
