#include <QMainWindow>
#include "db/User.h"
#include "widgets/DashboardWidget.h"

#ifndef CPP_TERM_PROJECT_USERDASHBOARD_H
#define CPP_TERM_PROJECT_USERDASHBOARD_H

class Dashboard : public QMainWindow {
Q_OBJECT

public:
    Dashboard(QWidget *parent = nullptr);

    void init();

    ~Dashboard();

public slots:

    void setUser(User user);
    void userLogOut();

signals:
    void logOut();

private:
    bool isEmployee = false;
    User user;

    DashboardWidget *mainWidget;
};

#endif //CPP_TERM_PROJECT_USERDASHBOARD_H
