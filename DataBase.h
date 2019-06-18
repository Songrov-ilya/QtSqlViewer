#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QColor>
#include <QBrush>

class DataBase
{
public:
    DataBase();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1);
    void addConnection(QString databaseName);
    bool openDefaultDataBase();
    bool openNewDB();
    /* Finish at the end */ void closeDB() { closeDataBase(); }

private:
    bool closeDataBase();
    bool setQuery();
    bool setNewQuery();

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
