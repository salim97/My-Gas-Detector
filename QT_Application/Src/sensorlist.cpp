#include "sensorlist.h"

SensorList::SensorList(QObject *parent) : QObject(parent)
{
    mItems.append({ "CARBON MONOXIDE", "MQ9", "150", "150 PPM", true, "#D77EFC" });
    mItems.append({ "Air Quality", "MQ135", "320", "320 PPM"  , true, "#FC6F61" });
    mItems.append({ "Temperateur", "DHT11_temperateur", "30", "30 C"  ,      true, "#18A0FA" });
    mItems.append({ "Humidity", "DHT11_humidity", "80", "80 %" ,          true, "#94C325"});
}

QVector<SensorItem> SensorList::items() const
{
    return mItems;
}

bool SensorList::setItemAt(int index, const SensorItem &item)
{

    if (index < 0 || index >= mItems.size())
        return false;

    const SensorItem &oldItem = mItems.at(index);
    if (item.sensorName == oldItem.sensorName
            && item.value == oldItem.value
            && item.description == oldItem.description
            && item.isConnected == oldItem.isConnected
            && item.title == oldItem.title)
        return false;

    mItems[index] = item;

    return true;
}

SensorItem SensorList::getItemAt(int index)
{
    return mItems.at(index);
}

int SensorList::findSensor(QString sensorName)
{
    for( int i = 0 ; i < mItems.length() ; i++ )
    {
        if(mItems[i].sensorName == sensorName )
            return i ;
    }
    return -1 ;
}

void SensorList::appendItem(SensorItem item)
{
    emit preItemAppended();

//    SensorItem item;
//    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}

void SensorList::removeCompletedItems()
{
    //TODO : remove all offline sensors ....
    // add bool to struct connected true false
    for (int i = 0; i < mItems.size(); ) {
        if (!mItems.at(i).isConnected) { // if connected == false then remove item from list
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        } else {
            ++i;
        }
    }
}
