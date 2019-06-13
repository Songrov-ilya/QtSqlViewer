#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    treeWidget { new QTreeWidget },
    tableView { new QTableView },
    lineEditName { new QLineEdit},
    labelName { new QLabel("Name")},
    lineEditAge { new QLineEdit},
    labelAge { new QLabel("Age")},
    pushButtonClear { new QPushButton("Clear line") },
    pushButtonEdit { new QPushButton("Edit") }
{
    setupActions();
    setupWidgets();


    dataBase.openDefaultDB();


    /* Finish at the end */showTableView("");
//    /* Finish at the end */refreshTreeWidget();


}

MainWindow::~MainWindow()
{

}

void MainWindow::setupActions()
{
    QMenuBar *menuBar { new QMenuBar(this) };
    QMenu *menuFile { new QMenu("File", menuBar) };
    QAction *actionOpenDB { new QAction("Open DB", menuFile) };
    QAction *actionQuit { new QAction("Quit", menuFile) };
    menuFile->addAction(actionOpenDB);
    menuFile->addAction(actionQuit);

    connect(actionOpenDB, &QAction::triggered, this, &MainWindow::onActionOpenDB);
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

    QHBoxLayout *hLayoutLine { new QHBoxLayout};
    QHBoxLayout *hLayoutButton { new QHBoxLayout};
    hLayoutLine->addWidget(lineEditName);
    hLayoutLine->addWidget(labelName);
    hLayoutLine->addWidget(lineEditAge);
    hLayoutLine->addWidget(labelAge);
    hLayoutButton->addWidget(pushButtonClear);
    hLayoutButton->addWidget(pushButtonEdit);

    QGridLayout *mainLayout { new QGridLayout};
    mainLayout->addWidget(treeWidget, 0, 0, 3, 1);
    treeWidget->setHeaderHidden(true);
    mainLayout->addWidget(tableView, 0, 1);
    mainLayout->addLayout(hLayoutLine, 1, 1);
    mainLayout->addLayout(hLayoutButton, 2, 1);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}

void MainWindow::onActionOpenDB()
{
    dataBase.openNewDB();
}

void MainWindow::onActionactionAboutApp()
{

}


void MainWindow::initializeModel(QSqlTableModel *model)
{
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
}

QTableView *MainWindow::createView(QTableView * view, QSqlTableModel *model, const QString &title)
{
    view->setModel(model);
    view->setWindowTitle(title);
    return view;
}

void MainWindow::showTableView(const QString &table)
{
    qDebug() << "showTable 2" << endl;
    QSqlTableModel *model = new QSqlTableModel(tableView, QSqlDatabase::database());
    model->setEditStrategy(QSqlTableModel::OnRowChange);
//    model->setTable(QSqlDatabase::database().driver()->escapeIdentifier(table, QSqlDriver::TableName));
    model->setTable(QSqlDatabase::database().tables().at(0));
    model->select();
//    if (model->lastError().type() != QSqlError::NoError)
//        emit statusMessage(model->lastError().text());

    tableView->setModel(model);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
//    connect(table->selectionModel(), &QItemSelectionModel::currentRowChanged,
//            this, &Browser::currentChanged);


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

    QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget);
    root->setText(0, qDBCaption(db));

    if (db.isOpen()) {
        QStringList tables = db.tables();
        for (int t = 0; t < tables.count(); ++t) {
            QTreeWidgetItem *table = new QTreeWidgetItem(root);
            table->setText(0, tables.at(t));
        }
    }

//    treeWidget->doItemsLayout(); // HACK

}
