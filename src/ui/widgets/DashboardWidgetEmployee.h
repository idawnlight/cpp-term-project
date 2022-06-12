#ifndef CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H
#define CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H

#include "DashboardWidget.h"
#include "UsersModel.h"
#include "DashBoardFinder.h"
#include "AccountWidget.h"
#include "RecordsModel.h"

class DashboardWidgetEmployee : public DashboardWidget {
    Q_OBJECT

public:
    DashboardWidgetEmployee(QWidget *parent = nullptr, const User& user = {});

public slots:
    void refreshUsersTable();
    void refreshRecordsTable();
    void activateButtons();
    void activateRedeemButton(const QItemSelection &selected, const QItemSelection &deselected);
    void addUser();
    void editUser();
    void deleteUser();
    void userChanged(User user);
    void userAdded(User user);
    void usersExport();
    void usersImport();
    void findAccount(const QModelIndex & index);
    void findRecords(int accountId);
    void fetchRecordsByAccountId(int accountId);
    void setInterestRate();
    void redeemFixedDeposit();

private:
    UsersModel* usersModel;
    QSortFilterProxyModel* usersModelProxy = new QSortFilterProxyModel(this);
    RecordsModel* recordsModel;
    QSortFilterProxyModel* recordsModelProxy = new QSortFilterProxyModel(this);
    QTableView* usersTable;
    QTableView* recordsTable;
    QPushButton* addButton = new QPushButton(tr("Add"));
    QPushButton* editButton = new QPushButton(tr("Edit"));
    QPushButton* deleteButton = new QPushButton(tr("Delete"));
    QPushButton* importButton = new QPushButton(tr("Import"));
    QPushButton* exportButton = new QPushButton(tr("Export"));
    QPushButton* redeemButton = new QPushButton(tr("Redeem"));
    QPushButton* interestButton = new QPushButton(tr("Set Interest Rate"));
    QTabWidget* tabWidget = new QTabWidget;
    DashBoardFinder* accountFinder = new DashBoardFinder;
    DashBoardFinder* recordFinder = new DashBoardFinder;
    AccountWidget* accountWidget = new AccountWidget{nullptr, -1};
    QLabel* interestRateLabel = new QLabel();
};


#endif //CPP_TERM_PROJECT_DASHBOARDWIDGETEMPLOYEE_H
