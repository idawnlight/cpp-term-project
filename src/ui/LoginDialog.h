#include <QDialog>
#include <QtWidgets>

#include "db/User.h"

#ifndef CPP_TERM_PROJECT_LOGINDIALOG_H
#define CPP_TERM_PROJECT_LOGINDIALOG_H


class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);

private:
    QLineEdit *nameText;
    QLineEdit *passwordText;
    void debugFillUser();
    void debugFillEmployee();

signals:
//    void loggedIn(User user);
    void userLoggedIn(User user);

public slots:
    void accept() override;

};


#endif //CPP_TERM_PROJECT_LOGINDIALOG_H
