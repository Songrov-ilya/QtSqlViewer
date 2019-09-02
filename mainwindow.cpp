#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    treeWidget { new QTreeWidget },
    tableView { new QTableView },
    pushButtonEdit { new QPushButton("Edit") },
    actionInsertRow  { new QAction("InsertRow", tableView) },
    actionDeleteRow  { new QAction("DeleteRow", tableView) }
{
    setupMenuBar();
    setupWidgets();
    setupConnections();


    dataBase.openDefaultDataBase();
    showTableView(0);
    refreshTreeWidget();

}

MainWindow::~MainWindow()
{

}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar { new QMenuBar(this) };
    QMenu *menuFile { new QMenu("File", menuBar) };
    QAction *actionOpenDB { new QAction("Open DataBase", menuFile) };
    QAction *actionMakeQuery { new QAction("Make Query", menuFile) };
    QAction *actionQuit { new QAction("Quit", menuFile) };
    menuFile->addAction(actionOpenDB);
    menuFile->addAction(actionMakeQuery);
    menuFile->addAction(actionQuit);

    connect(actionOpenDB, &QAction::triggered, this, &MainWindow::onActionOpenDB);
    connect(actionMakeQuery, &QAction::triggered, this, &MainWindow::onActionMakeQuery);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::close);

    QMenu *menuHelp { new QMenu("Help", this) };
    QAction *actionAboutApp { new QAction("About app", menuHelp) };
    QAction *actionAboutQt { new QAction("About Qt", menuHelp) };
    menuHelp->addAction(actionAboutApp);
    menuHelp->addAction(actionAboutQt);

    connect(actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(actionAboutApp, &QAction::triggered, this, &MainWindow::onActionactionAboutApp);

    menuBar->addMenu(menuFile);
    menuBar->addMenu(menuHelp);
    this->setMenuBar(menuBar);
}

void MainWindow::setupWidgets()
{
    QWidget *widget { new QWidget };

    QHBoxLayout *hLayoutButton { new QHBoxLayout};
    hLayoutButton->addWidget(pushButtonEdit, 1, Qt::AlignRight);

    QGridLayout *mainLayout { new QGridLayout};
    mainLayout->addWidget(treeWidget, 0, 0, 3, 1);
    treeWidget->setHeaderHidden(true);
    mainLayout->addWidget(tableView, 0, 1);
        mainLayout->addLayout(hLayoutButton, 2, 1);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    tableView->addAction(actionInsertRow);
    tableView->addAction(actionDeleteRow);
    tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
}

void MainWindow::setupConnections()
{
    connect(treeWidget, &QTreeWidget::activated, this, &MainWindow::slotShowTable);

    connect(actionInsertRow, &QAction::triggered, this, &MainWindow::slotActionInsertRow);
    connect(actionDeleteRow, &QAction::triggered, this, &MainWindow::slotActionDeleteRow);

    connect(pushButtonEdit, &QPushButton::clicked, this, &MainWindow::slotOnPushButtonEdit);
}

void MainWindow::onActionOpenDB()
{
    if(!dataBase.openNewDataBase()){
        return;
    }
    showTableView(0);
    refreshTreeWidget();
}

void MainWindow::onActionMakeQuery()
{
    QDialog dialogQuery;

    QVBoxLayout vBoxLayout;
    QTextEdit textEdit;
    QPushButton buttonSubmit("Submit");
    vBoxLayout.addWidget(&textEdit);
    vBoxLayout.addWidget(&buttonSubmit, 2, Qt::AlignRight);
    dialogQuery.setLayout(&vBoxLayout);

    connect(&buttonSubmit, &QPushButton::clicked, [&textEdit, &dialogQuery, this]()
    {
        QSqlQueryModel *model = new QSqlQueryModel(this->tableView);
        model->setQuery(QSqlQuery(textEdit.toPlainText()));
        this->tableView->setModel(model);
        this->refreshTreeWidget();

        if(model->lastError().type() != QSqlError::NoError){
            QMessageBox msgBox;
            msgBox.setInformativeText(model->lastError().text());
            msgBox.setStandardButtons(QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            msgBox.exec();
        }
        else{
            dialogQuery.close();
        }
    });

    dialogQuery.exec();
}

void MainWindow::onActionactionAboutApp()
{
    QDialog dialog;
    QLabel label;
    label.setText("It is application for viewing and editing databases. It also possible to create "
                  "tables and make queries.");
    QVBoxLayout lay;
    lay.addWidget(&label);
    dialog.setLayout(&lay);
    dialog.exec();
}


void MainWindow::slotOnPushButtonEdit()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
    if (!model) {
        return;
    }

    QString strMessage { "Error: "};

    if(!model->submitAll()){
        strMessage.append(model->lastError().text() + "\n");
        QMessageBox msgBox;
        msgBox.setText(strMessage);
        msgBox.exec();
    }

}

void MainWindow::slotActionInsertRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
    if (!model)
        return;

    QModelIndex insertModelIndex = tableView->currentIndex();
    int row = insertModelIndex.row() == -1 ? 0 : insertModelIndex.row();
    model->insertRow(row);
    insertModelIndex = model->index(row, 0);
    tableView->setCurrentIndex(insertModelIndex);
    tableView->edit(insertModelIndex);
}

void MainWindow::slotActionDeleteRow()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(tableView->model());
    if (!model)
        return;

    QModelIndex deleteModelIndex = tableView->currentIndex();
    model->removeRow(deleteModelIndex.row());

}



void MainWindow::showTableView(const int row)
{
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()){
        tableView->setModel(new CustomModelMy(tableView));
        return;
    }

    QSqlTableModel *model = new CustomModelMy(tableView, db);

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if(!db.tables().isEmpty()){
        model->setTable(db.tables().at(row));
    }
    model->select();

    tableView->setModel(model);
/* Finish at the end *///    tableView->setColumnHidden(0,true);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);

}

static QString qDBCaption(const QSqlDatabase &db)
{
    QString nm = db.driverName();
    nm.append(QLatin1Char(':'));
    if (!db.userName().isEmpty())
        nm.append(db.userName()).append(QLatin1Char('@'));
    nm.append(db.databaseName());
    return nm;
}

void MainWindow::refreshTreeWidget()
{
    treeWidget->clear();
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()){
        return;
    }

    QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget);
    root->setText(0, qDBCaption(db));

    if (db.isOpen()) {
        QStringList tables = db.tables();
        for (int t = 0; t < tables.count(); ++t) {
            QTreeWidgetItem *table = new QTreeWidgetItem(root);
            table->setText(0, tables.at(t));
        }
    }

    treeWidget->expandAll();
//    treeWidget->doItemsLayout(); // HACK

}
