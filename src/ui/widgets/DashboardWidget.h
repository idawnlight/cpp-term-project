#ifndef CPP_TERM_PROJECT_DASHBOARDWIDGET_H
#define CPP_TERM_PROJECT_DASHBOARDWIDGET_H

#include <QTabWidget>
#include <QtWidgets>
#include "db/User.h"

class DashboardWidget : public QWidget {
    Q_OBJECT

public:
    DashboardWidget(QWidget *parent = nullptr, const User& user = {});

public slots:
    void userInfo();

protected:
    User user;
    QVBoxLayout* mainLayout;
};


#endif //CPP_TERM_PROJECT_DASHBOARDWIDGET_H
