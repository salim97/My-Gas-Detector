#ifndef SENSORLIST_H
#define SENSORLIST_H


#include <QObject>
#include <QVector>
#include <QDebug>

struct SensorItem
{
    QString title;
    QString sensorName;
    QString value;
    QString description;
    bool isConnected;
    QString color ;
};

class SensorList : public QObject
{
    Q_OBJECT
public:
    explicit SensorList(QObject *parent = nullptr);

    QVector<SensorItem> items() const;

    bool setItemAt(int index, const SensorItem &item);
    int findSensor(QString sensorName) ;

    SensorItem getItemAt(int index);
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(SensorItem item);
    void removeCompletedItems();

private:
    QVector<SensorItem> mItems;
};

#endif // SENSORLIST_H
