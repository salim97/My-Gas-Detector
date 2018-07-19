#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include <QAbstractListModel>
#include <QDebug>

class SensorList;

class SensorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SensorList *list READ list WRITE setList)

public:
    explicit SensorModel(QObject *parent = nullptr);
    enum {
        TitleRole = Qt::UserRole,
        SensorNameRole,
        ValueRole,
        DescriptionRole,
        IsConnectedRole,
        colorRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    SensorList *list() const;
    void setList(SensorList *list);

private:
    SensorList *mList;
};


#endif // SENSORMODEL_H
