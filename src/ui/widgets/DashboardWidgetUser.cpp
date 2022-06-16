#include "DashboardWidgetUser.h"
#include "UserDialog.h"
#include "db/Db.h"

DashboardWidgetUser::DashboardWidgetUser(QWidget *parent, const User &user)
        : DashboardWidget(parent, user),
          recordsModel(new RecordsModel),
          recordsTable(new QTableView),
          depositsModel(new RecordsModel),
          depositsTable(new QTableView),
          accountWidget(new AccountWidget(this, user)) {
    refreshRecordsTable();

//    connect(accountWidget->currentContent, &AccountInfoLabel::doubleClicked, this,
//            &DashboardWidgetUser::listDeposits);
//    connect(accountWidget->savingsContent, &AccountInfoLabel::doubleClicked, this,
//            &DashboardWidgetUser::listDeposits);
    connect(accountWidget, &AccountWidget::savingsRecordsFind, this, &DashboardWidgetUser::listDeposits);
    connect(accountWidget, &AccountWidget::newRecord, this, &DashboardWidgetUser::recordChanged);

    auto accountTab = new QWidget;
    auto accountLayout = new QVBoxLayout;
    accountTab->setLayout(accountLayout);
    accountLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    accountLayout->addLayout(accountWidget);

//    connect(recordFinder, &DashBoardFinder::find, this, &DashboardWidgetUser::fetchRecordsByAccountId);

    tabWidget->addTab(accountTab, "Account");

    auto recordTab = new QWidget;
    auto recordLayout = new QVBoxLayout;
    auto recordTableLayout = new QHBoxLayout;
    recordTab->setLayout(recordLayout);
//    recordFinder->finder->setPlaceholderText("Account ID...");
//    recordLayout->addWidget(recordFinder);

//    auto recordsTableSelection = recordsTable->selectionModel();
//    connect(recordsTableSelection, &QItemSelectionModel::selectionChanged, this,
//            &DashboardWidgetUser::activateRedeemButton);
//    connect(redeemButton, &QAbstractButton::clicked, this, &DashboardWidgetUser::redeemFixedDeposit);

    recordTableLayout->addWidget(recordsTable);
//    recordTableLayout->addLayout(recordsSideLayout);
    recordLayout->addLayout(recordTableLayout);
    recordLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    tabWidget->addTab(recordTab, "Records");

    if (accountWidget->getSavingsAccount().id != -1) {
        refreshDepositsTable();
        auto depositsSideLayout = new QGridLayout;
        auto depositsSideTopLayout = new QVBoxLayout;
        depositsSideTopLayout->setAlignment(Qt::AlignTop);
        redeemButton->setEnabled(false);
        depositsSideTopLayout->addWidget(redeemButton);
        depositsSideLayout->addLayout(depositsSideTopLayout, 0, 0, Qt::AlignTop);

        auto depositTab = new QWidget;
        auto depositLayout = new QVBoxLayout;
        auto depositTableLayout = new QHBoxLayout;
        depositTableLayout->addWidget(depositsTable);
        depositTableLayout->addLayout(depositsSideLayout);
        depositLayout->addLayout(depositTableLayout);
        depositLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
        depositTab->setLayout(depositLayout);

        auto depositsTableSelection = depositsTable->selectionModel();
        connect(depositsTableSelection, &QItemSelectionModel::selectionChanged, this,
                &DashboardWidgetUser::activateRedeemButton);
        connect(redeemButton, &QAbstractButton::clicked, this, &DashboardWidgetUser::redeemFixedDeposit);

        tabWidget->addTab(depositTab, "Fixed Deposits");
    }

    mainLayout->addWidget(tabWidget);

    auto copyright = new QLabel("Rhine Bank, a Terran company");
    copyright->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(copyright);
}

void DashboardWidgetUser::refreshRecordsTable() {
    recordsModel->fetchDataByUserId(user.id);
    recordsModelProxy->setSourceModel(recordsModel);
    recordsTable->setModel(recordsModelProxy);
    recordsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    recordsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    recordsTable->verticalHeader()->hide();
    recordsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    recordsTable->setSortingEnabled(true);
    recordsTable->sortByColumn(0, Qt::DescendingOrder);
    recordsTable->setMinimumWidth(600);
}

void DashboardWidgetUser::refreshDepositsTable() {
    depositsModel->fetchDepositsByAccountId(accountWidget->getSavingsAccount().id);
    depositsModelProxy->setSourceModel(depositsModel);
    depositsTable->setModel(depositsModelProxy);
    depositsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    depositsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    depositsTable->verticalHeader()->hide();
    depositsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    depositsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    depositsTable->setSortingEnabled(true);
    depositsTable->sortByColumn(0, Qt::DescendingOrder);
    depositsTable->setMinimumWidth(600);
}

void DashboardWidgetUser::activateRedeemButton(const QItemSelection &selected, const QItemSelection &deselected) {
    auto depositsTableSelection = depositsTable->selectionModel();
    auto selectedRows = depositsTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto recordId = depositsModelProxy->data(row, Qt::EditRole).toInt();
    auto record = Db::getStorage().get<Record>(recordId);
    if (record.type == RecordType::FixedDeposit && !record.isRedeemed) {
        redeemButton->setEnabled(true);
    } else {
        redeemButton->setEnabled(false);
    }
}

void DashboardWidgetUser::listDeposits(int accountId) {
    tabWidget->setCurrentIndex(2);
}

void DashboardWidgetUser::recordChanged() {
    recordsModel->fetchDataByUserId(user.id);
    depositsModel->fetchDepositsByAccountId(accountWidget->getSavingsAccount().id);
    recordsModelProxy->invalidate();
    depositsModelProxy->invalidate();
}

void DashboardWidgetUser::redeemFixedDeposit() {
    auto depositsTableSelection = depositsTable->selectionModel();
    auto selectedRows = depositsTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto recordId = depositsModelProxy->data(row, Qt::EditRole).toInt();
    auto record = Db::getStorage().get<Record>(recordId);
    if (record.isRedeemed) return;
    auto start = QDateTime::fromString(record.time.c_str(), "yyyy.MM.dd hh:mm:ss");
    auto end = QDateTime::currentDateTime();
    int seconds = start.secsTo(end);
    int interest = (double) record.amount * record.interestRate / 100 * ((double) seconds / 31536000);
//    qDebug() << interest;
    int ret = QMessageBox::information(nullptr, tr("Redeem - Rhine Bank"),
                                       QString("After redeem you will get $%1 of interest, continue?").arg(
                                               QString::number((double) interest / 100, 'f', 2)),
                                       QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        accountWidget->getSavingsAccount().redeem(record, interest);
        depositsModel->fetchDepositsByAccountId(accountWidget->getSavingsAccount().id);
        accountWidget->fetchByUserId(accountWidget->getUser().id);
        recordChanged();
        redeemButton->setEnabled(false);
    }
}
