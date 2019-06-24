#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QColor>
#include <QBrush>


#include "ConnectionDialog.h"

class DataBase
{
public:
    DataBase();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1);
    bool addConnection(QString databaseName);
    bool openDefaultDataBase();
    bool openNewDataBase();
    void closeDataBase();

private:
    void setDefaultQuery();

};


class CustomModelMy: public QSqlTableModel
{
    Q_OBJECT
public:
    explicit CustomModelMy(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db) {}

    QVariant data(const QModelIndex &idx, int role) const override
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::red));
        return QSqlTableModel::data(idx, role);
    }
};

#endif // DATABASE_H
