#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>
#include "mypropertyhelper.h"
#include "sensormodel.h"

#define enable_debug_udp true

class MyNetwork : public QObject
{
    Q_OBJECT
public:
    explicit MyNetwork(QObject *parent = nullptr, SensorModel *sensorModel = nullptr);

signals:

public slots:
    void sendUDP(QString msg);

private slots:
    void readyReadUDP();

    void timeout();
private:
    int udpPort = 45454 ;
    QUdpSocket *m_udpSocket = nullptr;
    SensorModel *sensorModel;
    QTimer *timer ;
};

#endif // MYNETWORK_H
