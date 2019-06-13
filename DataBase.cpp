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

bool DataBase::openDefaultDB()
{
    /* Finish at the end  создавать новый файл, в том случае если он не существует. А так, открывать существующий*/
    addConnection("DataNameDefault");
    setQuery();
}

bool DataBase::openNewDB()
{
    closeDB();
    addConnection("DataNameFull");
}


bool DataBase::closeDB()
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
    query.exec("create table person (id int primary key, "
               "firstname varchar(20), lastname varchar(20))");
    query.exec("insert into person values(101, 'Danny', 'Young')");
    query.exec("insert into person values(102, 'Christine', 'Holand')");
    query.exec("insert into person values(103, 'Lars', 'Gordon')");
    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");


    query.exec("create table items (id int primary key,"
                                             "imagefile int,"
                                             "itemtype varchar(20),"
                                             "description varchar(100))");
    query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and  "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
    query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
    query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
    query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");

    query.exec("create table images (itemid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/qt-logo.png')");
    query.exec("insert into images values(1, 'images/qt-quick.png')");
    query.exec("insert into images values(2, 'images/qt-creator.png')");
    query.exec("insert into images values(3, 'images/qt-project.png')");

    qDebug() << "Text " << endl;

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
    q.exec("create table Names (id integer primary key, Firstname varchar, Lastname varchar, City varchar)");
    q.exec("insert into Names values (0, 'Sala', 'Palmer', 'Morristown')");
    q.exec("insert into Names values (1, 'Christopher', 'Walker', 'Morristown')");
    q.exec("insert into Names values (2, 'Donald', 'Duck', 'Andeby')");
    q.exec("insert into Names values (3, 'Buck', 'Rogers', 'Paris')");
    q.exec("insert into Names values (4, 'Sherlock', 'Holmes', 'London')");
    return q.isSelect();
}
