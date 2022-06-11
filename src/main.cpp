#include "utility.h"
#include "ui/LoginDialog.h"
#include "ui/Dashboard.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Utility::init();
//    std::string hashed = Utility::password_hash("Correct Horse Battery Staple");
//    if (Utility::password_verify("Correct Horse Battery Staple", hashed.c_str())) {
//        std::cout << "true";
//    }

//    if (Utility::checkIdNumber("440102198001021230")) {
//        qDebug() << "true";
//    } else {
//        qDebug() << "false";
//    }

    QApplication a(argc, argv);

    LoginDialog loginDialog;
    loginDialog.show();

//    MainWindow w;
//    QObject::connect(&loginDialog, &LoginDialog::loggedIn,
//                     &w, &MainWindow::setUser);

    Dashboard user;

    QObject::connect(&loginDialog, &LoginDialog::userLoggedIn,
                     &user, &Dashboard::setUser);

//    w.show();
    return a.exec();
}
