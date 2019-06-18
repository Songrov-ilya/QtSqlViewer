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
//    connectionWidget->refresh();

    return err;
}

void DataBase::addConnection(QString databaseName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        qWarning("Failed to open DataName.");
    }
}

bool DataBase::openDefaultDataBase()
{
    /* Finish at the end  создавать новый файл, в том случае если он не существует. А так, открывать существующий*/
    addConnection("DataNameDefault");
    setDefaultQuery();

}

bool DataBase::openNewDataBase()
{
    closeDataBase();
    addConnection("DataNameFull");
}


bool DataBase::closeDataBase()
{
    qDebug() << "Text close -11 " << endl;
    QString strDb = QSqlDatabase::database().connectionName();
    qDebug() << "Text close 11 " << strDb << endl;
    QSqlDatabase::database(strDb).close();
    QSqlDatabase::removeDatabase(strDb);

    qDebug() << "Text close 22 " << endl;
}

bool DataBase::setDefaultQuery()
{
    QSqlQuery query;
    query.exec("create table person (id INTEGER primary key AUTOINCREMENT, "
               "name TEXT (20), age INTEGER)");
    query.exec("insert into person (name, age) values ('Danny', 23)");
    query.exec("insert into person (name, age) values ('Christine', 34)");
    query.exec("insert into person (name, age) values ('Lars', 35)");
    query.exec("insert into person (name, age) values ('Roberto', 36)");
    query.exec("insert into person (name, age) values ('Maria', 36)");
    query.exec("SELECT * from person");

//    query.exec("create table person (id INTEGER primary key AUTOINCREMENT, name TEXT (20), age INTEGER)");
//    query.exec("SELECT name from person");

    return true;
}
