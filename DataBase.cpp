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
    setQuery();
}

bool DataBase::openNewDB()
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

bool DataBase::setQuery()
{
    QSqlQuery query;
    query.exec("create table person (id INTEGER primary key AUTOINCREMENT, "
               "name TEXT (20), age INTEGER)");
    query.exec("insert into person (name, age) values ('Danny', 23)");
    query.exec("insert into person (name, age) values ('Christine', 34)");
    query.exec("insert into person (name, age) values ('Lars', 35)");
    query.exec("insert into person (name, age) values ('Roberto', 36)");
    query.exec("insert into person (name, age) values ('Maria', 36)");


    return true;

}

bool DataBase::setNewQuery()
{
    QSqlQuery q("");
    q.exec("drop table Movies");
    q.exec("drop table Names");
    q.exec("create table Movies (id integer primary key, Title varchar, Director varchar, Rating number)");
    q.exec("insert into Movies values (0, 'Metropolis', 'Fritz Lang', '8.4')");
    q.exec("insert into Movies values (1, 'Nosferatu, eine Symphonie des Grauens', 'F.W. Murnau', '8.1')");
    q.exec("insert into Movies values (2, 'Bis ans Ende der Welt', 'Wim Wenders', '6.5')");
    q.exec("insert into Movies values (3, 'Hardware', 'Richard Stanley', '5.2')");
    q.exec("insert into Movies values (4, 'Mitchell', 'Andrew V. McLaglen', '2.1')");
    q.exec("create table Names (id integer primary key, name varchar, age varchar, City varchar)");
    q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
    q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
    q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
    q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
    q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");
    return q.isSelect();
}
