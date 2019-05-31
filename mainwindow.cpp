#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupActions();
    setupWidgets();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupActions()
{
    QMenuBar *menuBar { new QMenuBar(this) };
    QMenu *menuFile { new QMenu("File", menuBar) };
    QAction *actionOpen { new QAction("Open DB", menuFile) };
    QAction *actionQuit { new QAction("Quit", menuFile) };
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionQuit);
    connect(actionQuit, &QAction::triggered, this, &MainWindow::close);

    QMenu *menuHelp { new QMenu("Help", this) };
    QAction *actionAboutApp { new QAction("About app", menuHelp) };
    QAction *actionAboutQt { new QAction("About Qt", menuHelp) };
    menuHelp->addAction(actionAboutApp);
    menuHelp->addAction(actionAboutQt);

    connect(actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

    menuBar->addMenu(menuFile);
    menuBar->addMenu(menuHelp);
    this->setMenuBar(menuBar);
}

void MainWindow::setupWidgets()
{
    QWidget *widget { new QWidget };
    QTableView *tableView { new QTableView(this)};
    QLineEdit *lineEditName { new QLineEdit};
    QLabel *labelName { new QLabel("Name")};
    QLineEdit *lineEditAge { new QLineEdit};
    QLabel *labelAge { new QLabel("Age")};
    QPushButton *pushButtonClear = new QPushButton("Clear line");
    QPushButton *pushButtonEdit = new QPushButton("Edit");

    QHBoxLayout *hLayoutLine { new QHBoxLayout};
    QHBoxLayout *hLayoutButton { new QHBoxLayout};
    hLayoutLine->addWidget(lineEditName);
    hLayoutLine->addWidget(labelName);
    hLayoutLine->addWidget(lineEditAge);
    hLayoutLine->addWidget(labelAge);
    hLayoutButton->addWidget(pushButtonClear);
    hLayoutButton->addWidget(pushButtonEdit);

    QVBoxLayout *mainLayout { new QVBoxLayout};
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(hLayoutLine);
    mainLayout->addLayout(hLayoutButton);
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}
