#include "utility.h"
#include "ui/LoginDialog.h"
#include "ui/Dashboard.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    Utility::init();

    QApplication app(argc, argv);

    LoginDialog loginDialog;
    loginDialog.show();

    Dashboard dashboard;

    QObject::connect(&loginDialog, &LoginDialog::userLoggedIn,
                     &dashboard, &Dashboard::setUser);

    return app.exec();
}
