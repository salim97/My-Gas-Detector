#include "sensormodel.h"
#include "sensorlist.h"

SensorModel::SensorModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int SensorModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant SensorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const SensorItem item = mList->items().at(index.row());
    switch (role) {
    case TitleRole:
        return QVariant(item.title);
    case SensorNameRole:
        return QVariant(item.sensorName);
    case ValueRole:
        return QVariant(item.value);
    case DescriptionRole:
        return QVariant(item.description);
    case IsConnectedRole:
        return QVariant(item.isConnected);
    case colorRole:
        return QVariant(item.color);
    }

    return QVariant();
}

bool SensorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    SensorItem item = mList->items().at(index.row());
    switch (role) {
    case TitleRole:
        item.title = value.toString();
        break;
    case SensorNameRole:
        item.sensorName = value.toString();
        break;
    case ValueRole:
        item.value = value.toString();
        break;
    case DescriptionRole:
        item.description = value.toString();
        break;
    case IsConnectedRole:
        item.isConnected = value.toBool();
        break;
    case colorRole:
        item.color = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags SensorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> SensorModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[SensorNameRole] = "sensorName";
    names[ValueRole] = "value";
    names[DescriptionRole] = "description";
    names[IsConnectedRole] = "isConnected";
    names[colorRole] = "color";
    return names;
}

SensorList *SensorModel::list() const
{
    return mList;
}

void SensorModel::setList(SensorList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &SensorList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &SensorList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &SensorList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
//        connect(mList, &SensorList::itemChanged, this, [=](int index) {


//        });
    }

    endResetModel();
}
