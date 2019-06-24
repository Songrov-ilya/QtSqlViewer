#include <QFileDialog>
#include "ConnectionDialog.h"

ConnectionDialog::ConnectionDialog()
{
    setWidgets();
    setConnections();
}

void ConnectionDialog::setWidgets()
{

    vboxLayout = new QVBoxLayout(this);

    connectionGroupBox = new QGroupBox("Connection settings", this);
    lineEditDriver = new QLineEdit(connectionGroupBox);
    lineEditDriver->setText("QSQLITE");
    lineEditDriver->setReadOnly(true);
    textLabelDriver = new QLabel("D&river", connectionGroupBox);
    textLabelUsername = new QLabel("&Username:", connectionGroupBox);
    editDatabase = new QLineEdit(connectionGroupBox);
    QAction *actionPoints = new QAction(QIcon(":/new/IconConnection/Point.png"), "");
    editDatabase->addAction(actionPoints, QLineEdit::TrailingPosition);
    connect(actionPoints, &QAction::triggered, [&]()
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
        editDatabase->setText(fileName);
    });
    textLabeDatabaseName = new QLabel("Database Name:", connectionGroupBox);
    editUsername = new QLineEdit(connectionGroupBox);
    editPassword = new QLineEdit(connectionGroupBox);
    editHostname = new QLineEdit(connectionGroupBox);
    textLabelHostname = new QLabel("&Hostname:", connectionGroupBox);
    textLabelPort = new QLabel("P&ort:", connectionGroupBox);
    textLabelPassword = new QLabel("&Password:", connectionGroupBox);
    portSpinBox = new QSpinBox(connectionGroupBox);
    portSpinBox->setMaximum(65535);
    portSpinBox->setMinimum(-1);
    portSpinBox->setValue(-1);
    portSpinBox->setSpecialValueText("Default");
    editPassword->setEchoMode(QLineEdit::Password);

    okButton = new QPushButton("&OK", this);
    cancelButton = new QPushButton("&Cancel", this);
    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout = new QGridLayout(connectionGroupBox);
    gridLayout->setContentsMargins(8, 8, 8, 8);
    gridLayout->addWidget(lineEditDriver, 0, 1, 1, 1);
    gridLayout->addWidget(textLabelUsername, 2, 0, 1, 1);
    gridLayout->addWidget(textLabelDriver, 0, 0, 1, 1);
    gridLayout->addWidget(editDatabase, 1, 1, 1, 1);
    gridLayout->addWidget(portSpinBox, 5, 1, 1, 1);
    gridLayout->addWidget(textLabeDatabaseName, 1, 0, 1, 1);
    gridLayout->addWidget(editPassword, 3, 1, 1, 1);
    gridLayout->addWidget(editUsername, 2, 1, 1, 1);
    gridLayout->addWidget(editHostname, 4, 1, 1, 1);
    gridLayout->addWidget(textLabelHostname, 4, 0, 1, 1);
    gridLayout->addWidget(textLabelPort, 5, 0, 1, 1);
    gridLayout->addWidget(textLabelPassword, 3, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    hboxLayout->addItem(spacerItem);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    hboxLayout1->addItem(spacerItem1);
    hboxLayout1->addWidget(okButton);
    hboxLayout1->addWidget(cancelButton);

    vboxLayout->addWidget(connectionGroupBox);
    vboxLayout->addLayout(hboxLayout);
    vboxLayout->addLayout(hboxLayout1);

#ifndef QT_NO_SHORTCUT
    textLabelUsername->setBuddy(editUsername);
    textLabelDriver->setBuddy(lineEditDriver);
    textLabeDatabaseName->setBuddy(editDatabase);
    textLabelHostname->setBuddy(editHostname);
    textLabelPort->setBuddy(portSpinBox);
    textLabelPassword->setBuddy(editPassword);
#endif // QT_NO_SHORTCUT
    QWidget::setTabOrder(lineEditDriver, editDatabase);
    QWidget::setTabOrder(editDatabase, editUsername);
    QWidget::setTabOrder(editUsername, editPassword);
    QWidget::setTabOrder(editPassword, editHostname);
    QWidget::setTabOrder(editHostname, portSpinBox);
    QWidget::setTabOrder(portSpinBox, okButton);
    QWidget::setTabOrder(okButton, cancelButton);

    okButton->setDefault(true);
}

void ConnectionDialog::setConnections()
{
    connect(okButton, &QPushButton::clicked, this, &ConnectionDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ConnectionDialog::reject);
}


QString ConnectionDialog::driverName() const
{
    return lineEditDriver->text();
}

QString ConnectionDialog::databaseName() const
{
    return editDatabase->text();
}

QString ConnectionDialog::userName() const
{
    return editUsername->text();
}

QString ConnectionDialog::password() const
{
    return editPassword->text();
}

QString ConnectionDialog::hostName() const
{
    return editHostname->text();
}

int ConnectionDialog::port() const
{
    return portSpinBox->value();
}




