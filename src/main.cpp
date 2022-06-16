#include "utility.h"
#include "ui/LoginDialog.h"
#include "ui/Dashboard.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Utility::init();
//    qDebug() << Utility::checkPhoneNumber("139112421135");

    QApplication app(argc, argv);

    LoginDialog loginDialog;
    loginDialog.show();

    Dashboard dashboard;

    QObject::connect(&loginDialog, &LoginDialog::userLoggedIn,
                     &dashboard, &Dashboard::setUser);
    QObject::connect(&dashboard, &Dashboard::logOut,
                     &loginDialog, &LoginDialog::logOut);

    return app.exec();
}
