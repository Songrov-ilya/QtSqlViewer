#include "DataBase.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QObject>


DataBase::DataBase()
{

}

QSqlError DataBase::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                  const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString("DataName%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user, passwd)) {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("DataName%1").arg(cCount));
    }

    return err;
}

bool DataBase::addConnection(QString databaseName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qWarning("Failed to open DataName.");
        return false;
    }
    return true;
}

bool DataBase::openDefaultDataBase()
{
    /* Finish at the end  создавать новый файл, в том случае если он не существует. А так, открывать существующий*/
    bool boolOpen { addConnection("DataNameDefault") };
    setDefaultQuery();

    return boolOpen;
}

bool DataBase::openNewDataBase()
{
    ConnectionDialog connDialog;
    connDialog.exec();
//    closeDataBase();
//    bool boolOpen { addConnection("DataNameFull") };
//    return boolOpen;
}


void DataBase::closeDataBase()
{
    QString strDb = QSqlDatabase::database().connectionName();
    QSqlDatabase::database(strDb).close();
    QSqlDatabase::removeDatabase(strDb);
}

void DataBase::setDefaultQuery()
{
    QSqlQuery query;
    query.exec("create table person (id INTEGER primary key AUTOINCREMENT, "
               "name TEXT (20), age INTEGER)");
    query.exec("insert into person (name, age) values ('Danny', 23)");
    query.exec("insert into person (name, age) values ('Christine', 34)");
    query.exec("insert into person (name, age) values ('Lars', 35)");
    query.exec("insert into person (name, age) values ('Roberto', 36)");
    query.exec("insert into person (name, age) values ('Maria', 36)");
}
