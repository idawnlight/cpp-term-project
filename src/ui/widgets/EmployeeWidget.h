#ifndef CPP_TERM_PROJECT_EMPLOYEEWIDGET_H
#define CPP_TERM_PROJECT_EMPLOYEEWIDGET_H

#include "DashboardWidget.h"
#include "UsersModel.h"

class EmployeeWidget : public DashboardWidget {
    Q_OBJECT

public:
    EmployeeWidget(QWidget *parent = nullptr, const User& user = {});

public slots:
    void refreshTable();
    void activateButtons();
    void addUser();
    void editUser();
    void deleteUser();
    void userChanged(User user);
    void userAdded(User user);

private:
    UsersModel* usersModel;
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    QTableView* usersTable;
    QTableView* accountsTable;
    QPushButton* addButton = new QPushButton(tr("Add"));
    QPushButton* editButton = new QPushButton(tr("Edit"));
    QPushButton* deleteButton = new QPushButton(tr("Delete"));
};


#endif //CPP_TERM_PROJECT_EMPLOYEEWIDGET_H
