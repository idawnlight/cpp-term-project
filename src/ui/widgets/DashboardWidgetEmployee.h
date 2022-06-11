#ifndef CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H
#define CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H

#include "DashboardWidget.h"
#include "UsersModel.h"
#include "DashBoardFinder.h"
#include "AccountWidget.h"

class DashboardWidgetEmployee : public DashboardWidget {
    Q_OBJECT

public:
    DashboardWidgetEmployee(QWidget *parent = nullptr, const User& user = {});

public slots:
    void refreshTable();
    void activateButtons();
    void addUser();
    void editUser();
    void deleteUser();
    void userChanged(User user);
    void userAdded(User user);
    void usersExport();
    void usersImport();

private:
    UsersModel* usersModel;
    QSortFilterProxyModel* usersModelProxy = new QSortFilterProxyModel(this);
    QTableView* usersTable;
    QTableView* accountsTable;
    QPushButton* addButton = new QPushButton(tr("Add"));
    QPushButton* editButton = new QPushButton(tr("Edit"));
    QPushButton* deleteButton = new QPushButton(tr("Delete"));
    QPushButton* importButton = new QPushButton(tr("Import"));
    QPushButton* exportButton = new QPushButton(tr("Export"));
    DashBoardFinder* accountFinder = new DashBoardFinder;
    DashBoardFinder* recordFinder = new DashBoardFinder;
    AccountWidget* accountWidget = new AccountWidget{nullptr, -1};
};


#endif //CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H
