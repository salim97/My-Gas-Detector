#include "mynetwork.h"


MyNetwork::MyNetwork(QObject *parent, SensorModel *sensorList) : QObject(parent)
{
    this->sensorModel = sensorList ;
    m_udpSocket = new QUdpSocket(this);
    if(!m_udpSocket->bind(udpPort, QUdpSocket::ShareAddress )) //
        qDebug() << "m_udpSocket : " + m_udpSocket->errorString()  ;
    else
        qDebug() <<"UDP bind 127.0.0.1:" +QString::number(udpPort)+" LISTENING." ;

    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readyReadUDP()));

    timer = new QTimer(this) ;
    timer->setInterval(125);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

void MyNetwork::sendUDP(QString msg)
{
    if(enable_debug_udp)
        qDebug() << "sendUDP: " << msg ;
    QByteArray datagram = msg.toLatin1() ;
    m_udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, udpPort);
}

void MyNetwork::readyReadUDP()
{
//    while (m_udpSocket->hasPendingDatagrams())
//    {
//        QByteArray datagram;
//        datagram.resize(m_udpSocket->pendingDatagramSize());
//        m_udpSocket->readDatagram(datagram.data(), datagram.size());

//        QString data = datagram;
//        if(enable_debug_udp)
//            qDebug() << "readyReadUDP: " << data ;

//        if(data.contains("<MQ135>"))
//        {
//            data.replace("<MQ135>","");
//            int index = sensorModel->findSensor("<MQ135>") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.sensorName = "MQ135";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }
//        if(data.contains("<MQ9>"))
//        {
//            data.replace("<MQ9>","");
//            int index = sensorModel->findSensor("<MQ9>") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.sensorName = "MQ9";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }
//        if(data.contains("<DHT11_temperateur>"))
//        {
//            data.replace("<DHT11_temperateur>","");
//            int index = sensorModel->findSensor("<DHT11_temperateur>") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.title = "Temperateur" ;
//                tmp.sensorName = "DHT11";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }
//        if(data.contains("<DHT11_humidity>"))
//        {
//            data.replace("<DHT11_humidity>","");
//            int index = sensorModel->findSensor("<DHT11_humidity>") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.title = "Humidity" ;
//                tmp.sensorName = "DHT11";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }

//    }
}
int khra = 0 ;
void MyNetwork::timeout()
{

        QStringList ids ;
        ids << "<MQ135>" << "<MQ9>" << "<DHT11_temperateur>" << "<DHT11_humidity>" ;
        int randomIndex = qrand() % 4 ;
        QString data = ids[khra++ % 4] +QString::number(qrand() % 255) ;

        //if(enable_debug_udp)
            qDebug() << "timeout: " << data ;

        if(data.contains("<MQ135>"))
        {
            data.replace("<MQ135>","");
            for( int i = 0 ; i < sensorModel->rowCount() ; i++ )
            {
                if( sensorModel->data(sensorModel->index(i, 0), SensorModel::SensorNameRole).toString() == "MQ135")
                {
                    qDebug() << sensorModel->setData(sensorModel->index(i, 0), data+" PPM", SensorModel::DescriptionRole);
                }

            }
        }
        else if(data.contains("<MQ9>"))
        {
            data.replace("<MQ9>","");
            for( int i = 0 ; i < sensorModel->rowCount() ; i++ )
            {
                if( sensorModel->data(sensorModel->index(i, 0), SensorModel::SensorNameRole).toString() == "MQ9")
                {
                    sensorModel->setData(sensorModel->index(i, 0), data+" PPM", SensorModel::DescriptionRole);
                }

            }
        }
        else if(data.contains("<DHT11_temperateur>"))
        {
            data.replace("<DHT11_temperateur>","");
            for( int i = 0 ; i < sensorModel->rowCount() ; i++ )
            {
                if( sensorModel->data(sensorModel->index(i, 0), SensorModel::SensorNameRole).toString() == "DHT11_temperateur")
                {
                    qDebug() << sensorModel->setData(sensorModel->index(i, 0), data+" C", SensorModel::DescriptionRole);
                }

            }
        }
        else if(data.contains("<DHT11_humidity>"))
        {
            data.replace("<DHT11_humidity>","");
            for( int i = 0 ; i < sensorModel->rowCount() ; i++ )
            {
                if( sensorModel->data(sensorModel->index(i, 0), SensorModel::SensorNameRole).toString() == "DHT11_humidity")
                {
                    qDebug() << sensorModel->setData(sensorModel->index(i, 0), data+" %", SensorModel::DescriptionRole);
                }

            }
        }
//        if(data.contains("<MQ9>"))
//        {
//            data.replace("<MQ9>","");
//            int index = sensorModel->findSensor("MQ9") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.sensorName = "MQ9";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }
//        if(data.contains("<DHT11_temperateur>"))
//        {
//            data.replace("<DHT11_temperateur>","");
//            int index = sensorModel->findSensor("DHT11_temperateur") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.title = "Temperateur" ;
//                tmp.sensorName = "DHT11";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }
//        if(data.contains("<DHT11_humidity>"))
//        {
//            data.replace("<DHT11_humidity>","");
//            int index = sensorModel->findSensor("DHT11_humidity") ;
//            if( index != -1 )
//            {
//                SensorItem tmp = sensorModel->getItemAt(index) ;
//                tmp.value = data ;
//                sensorModel->setItemAt(index, tmp ) ;
//            }
//            else
//            {
//                SensorItem tmp ;
//                tmp.title = "Humidity" ;
//                tmp.sensorName = "DHT11";
//                tmp.value = data ;
//                sensorModel->appendItem(tmp);
//            }
//        }


}
