#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

class DataBase
{
public:
    DataBase();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1);
    void addConnection(QString databaseName);
    bool openDefaultDB();
    bool openNewDB();


private:
    bool closeDB();
    bool setQuery();
    bool setNewQuery();

};

#endif // DATABASE_H
