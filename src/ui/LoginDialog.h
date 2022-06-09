#include <QDialog>
#include <QtWidgets>

// #include "db/User.h"
#include "db/Employee.h"

#ifndef CPP_TERM_PROJECT_LOGINDIALOG_H
#define CPP_TERM_PROJECT_LOGINDIALOG_H


class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);

private:
    QLineEdit *nameText;
    QLineEdit *passwordText;

signals:
//    void loggedIn(User user);
    void userLoggedIn(User user);
    void employeeLoggedIn(Employee employee);

public slots:
    void accept() override;

};


#endif //CPP_TERM_PROJECT_LOGINDIALOG_H
