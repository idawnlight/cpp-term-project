#include "Dashboard.h"
#include "ui/widgets/UserDialog.h"
#include "widgets/DashboardWidgetEmployee.h"
#include "ui/widgets/DashboardWidgetUser.h"

#include <utility>
#include <QtWidgets>

Dashboard::Dashboard(QWidget *parent) : QMainWindow(parent) {

}

void Dashboard::init() {
    setWindowTitle(isEmployee ? "Employee - Rhine Bank" : "User - Rhine Bank");
    if (isEmployee) {
        mainWidget = new DashboardWidgetEmployee(this, user);
    } else {
        mainWidget = new DashboardWidgetUser(this, user);
    }
    connect(mainWidget, &DashboardWidget::logOut, this, &Dashboard::userLogOut);
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

void Dashboard::userLogOut() {
    hide();
    emit logOut();
}
