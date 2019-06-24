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
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
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
    bool boolOpen { addConnection("DataNameDefault") };
    setDefaultQuery();

    return boolOpen;
}

bool DataBase::openNewDataBase()
{
    bool boolOpen { false };

    ConnectionDialog connDialog;
    if(connDialog.exec() == QDialog::Accepted)
    {
        closeDataBase();
        QSqlError err = addConnection(connDialog.driverName(), connDialog.databaseName(), connDialog.hostName(),
                      connDialog.userName(), connDialog.password(), connDialog.port());
        if (err.type() != QSqlError::NoError) {
            QMessageBox::warning(&connDialog, QObject::tr("Unable to open database"),
                QObject::tr("An error occurred while opening the connection: ") + err.text());
        }
        boolOpen = true;
    }

    return boolOpen;
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
    query.exec("DROP table sqlite_sequence");
    query.exec("DROP table person");
    query.exec("Truncate table person");
    query.exec("create table if not exists person (id INTEGER primary key AUTOINCREMENT, "
               "name TEXT (20), age INTEGER)");
    query.exec("insert into person (name, age) values ('Ilya', 24)");
    query.exec("insert into person (name, age) values ('Yarik', 21)");
    query.exec("insert into person (name, age) values ('Anjela', 21)");
    query.exec("insert into person (name, age) values ('Roberto', 36)");
    query.exec("insert into person (name, age) values ('Maria', 36)");
}
