#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSqlTableModel>

#include "DataBase.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTreeWidget *treeWidget;
    QTableView *tableView;
    QLineEdit *lineEditName;
    QLabel *labelName;
    QLineEdit *lineEditAge;
    QLabel *labelAge;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonEdit;

    DataBase dataBase;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupActions();
    void setupWidgets();

public slots:
    void onActionOpenDB();
    void onActionactionAboutApp();


private:
    void initializeModel(QSqlTableModel *model);
    QTableView *createView(QTableView * view, QSqlTableModel *model, const QString &title = "");
    void showTableView(const QString &table);
    void refreshTreeWidget();


};

#endif // MAINWINDOW_H
