#ifndef CPP_TERM_PROJECT_DASHBOARDWIDGETUSER_H
#define CPP_TERM_PROJECT_DASHBOARDWIDGETUSER_H

#include "DashboardWidget.h"
#include "UsersModel.h"
#include "DashBoardFinder.h"
#include "AccountWidget.h"
#include "RecordsModel.h"

class DashboardWidgetUser : public DashboardWidget {
    Q_OBJECT

public:
    DashboardWidgetUser(QWidget *parent = nullptr, const User &user = {});

public slots:
    void refreshRecordsTable();
    void refreshDepositsTable();
    void activateRedeemButton(const QItemSelection &selected, const QItemSelection &deselected);
    void listDeposits(int accountId);
    void recordChanged();
    void redeemFixedDeposit();

private:
    RecordsModel *recordsModel;
    QSortFilterProxyModel *recordsModelProxy = new QSortFilterProxyModel(this);
    QTableView *recordsTable;
    RecordsModel *depositsModel;
    QSortFilterProxyModel *depositsModelProxy = new QSortFilterProxyModel(this);
    QTableView *depositsTable;
    QPushButton *redeemButton = new QPushButton(tr("Redeem"));
    QTabWidget *tabWidget = new QTabWidget;
    AccountWidget *accountWidget = new AccountWidget{nullptr, -1};
};


#endif //CPP_TERM_PROJECT_DASHBOARDWIDGETUSER_H
