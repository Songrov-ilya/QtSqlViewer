#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtWidgets>

class ConnectionDialog : public QDialog
{
public:
    ConnectionDialog();

    QVBoxLayout *vboxLayout;
    QGroupBox *connectionGroupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEditDriver;
    QLabel *textLabelUsername;
    QLabel *textLabelDriver;
    QLineEdit *editDatabase;
    QSpinBox *portSpinBox;
    QLabel *textLabeDatabaseName;
    QLineEdit *editPassword;
    QLineEdit *editUsername;
    QLineEdit *editHostname;
    QLabel *textLabelHostname;
    QLabel *textLabelPort;
    QLabel *textLabelPassword;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *okButton;
    QPushButton *cancelButton;


    void setWidgets();

    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;

};

#endif // CONNECTIONDIALOG_H
