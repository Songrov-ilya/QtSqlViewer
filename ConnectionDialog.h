#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QtWidgets>

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    ConnectionDialog();

    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private:

    QVBoxLayout *vboxLayout;
    QGroupBox *connectionGroupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEditDriver;
    QLabel *textLabelUsername;
    QLabel *textLabelDriver;
    QLineEdit *editDatabase;
    QSpinBox *portSpinBox;
    QLabel *textLabeDatabaseName;
    QLineEdit *editUsername;
    QLineEdit *editPassword;
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
    void setConnections();

};

#endif // CONNECTIONDIALOG_H
