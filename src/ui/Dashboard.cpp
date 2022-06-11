#include "Dashboard.h"
#include "widgets/DashboardWidgetEmployee.h"
#include "ui/widgets/UserDialog.h"

#include <utility>
#include <QtWidgets>

Dashboard::Dashboard(QWidget *parent) : QMainWindow(parent) {

}

void Dashboard::init() {
    setWindowTitle(isEmployee ? "Employee - Azure Bank" : "User - Azure Bank");
    if (isEmployee) {
        mainWidget = new DashboardWidgetEmployee(this, user);
    }
    setCentralWidget(mainWidget);
}

Dashboard::~Dashboard() = default;

void Dashboard::setUser(User loggedIn) {
    user = std::move(loggedIn);
    isEmployee = (user.employeeId > 0);
//    UserDialog userDialog{this, user, false};
//    userDialog.exec();
    init();
    show();
}
