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
    QLineEdit *lineEditAge;
    QLabel *labelAge;
    QPushButton *pushButtonEdit;

    QAction *actionInsertRow;
    QAction *actionDeleteRow;

    DataBase dataBase;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupMenuBar();
    void setupWidgets();
    void setupConnections();


private:
    void showTableView(const int row);
    void refreshTreeWidget();

public slots:
    void onActionOpenDB();
    void onActionMakeQuery();
    void onActionactionAboutApp();
    void slotShowTable(const QModelIndex &index) { showTableView (index.row()); }
    void slotOnPushButtonEdit();

private slots:
    void slotActionInsertRow();
    void slotActionDeleteRow();


};

#endif // MAINWINDOW_H
