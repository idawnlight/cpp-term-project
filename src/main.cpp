#include "mainwindow.h"
#include "utility.h"
#include "ui/LoginDialog.h"
#include "ui/UserDashboard.h"
#include "ui/EmployeeDashboard.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Utility::init();
//    std::string hashed = Utility::password_hash("Correct Horse Battery Staple");
//    if (Utility::password_verify("Correct Horse Battery Staple", hashed.c_str())) {
//        std::cout << "true";
//    }
    QApplication a(argc, argv);

    LoginDialog loginDialog;
    loginDialog.show();

//    MainWindow w;
//    QObject::connect(&loginDialog, &LoginDialog::loggedIn,
//                     &w, &MainWindow::setUser);

    UserDashboard user;
    EmployeeDashboard employee;

    QObject::connect(&loginDialog, &LoginDialog::userLoggedIn,
                     &user, &UserDashboard::setUser);
    QObject::connect(&loginDialog, &LoginDialog::employeeLoggedIn,
                     &employee, &EmployeeDashboard::setUser);

//    w.show();
    return a.exec();
}
