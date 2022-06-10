#ifndef CPP_TERM_PROJECT_EMPLOYEEWIDGET_H
#define CPP_TERM_PROJECT_EMPLOYEEWIDGET_H

#include "DashboardWidget.h"
#include "UsersModel.h"

class EmployeeWidget : public DashboardWidget {
    Q_OBJECT

public:
    EmployeeWidget(QWidget *parent = nullptr, const User& user = {});

private:
    UsersModel* usersModel;
    QTableView* usersTable;
    QTableView* accountsTable;
};


#endif //CPP_TERM_PROJECT_EMPLOYEEWIDGET_H
