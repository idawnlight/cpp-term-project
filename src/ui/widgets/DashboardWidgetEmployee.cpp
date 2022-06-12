#include "DashboardWidgetEmployee.h"
#include "UserDialog.h"
#include "db/Db.h"

DashboardWidgetEmployee::DashboardWidgetEmployee(QWidget *parent, const User &user)
        : DashboardWidget(parent, user),
          usersModel(new UsersModel),
          recordsModel(new RecordsModel),
          usersTable(new QTableView),
          recordsTable(new QTableView) {
    refreshUsersTable();
    refreshRecordsTable();

    auto usersTableSelection = usersTable->selectionModel();
    connect(usersTableSelection, &QItemSelectionModel::selectionChanged, this,
            &DashboardWidgetEmployee::activateButtons);

    auto usersTab = new QWidget;
    auto usersLayout = new QHBoxLayout();

    auto sideLayout = new QGridLayout;
    auto sideTopLayout = new QVBoxLayout;
    sideTopLayout->setAlignment(Qt::AlignTop);
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    sideTopLayout->addWidget(addButton);
    sideTopLayout->addWidget(editButton);
    sideTopLayout->addWidget(deleteButton);
    sideLayout->addLayout(sideTopLayout, 0, 0, Qt::AlignTop);

    auto sideBottomLayout = new QVBoxLayout;
    sideBottomLayout->setAlignment(Qt::AlignBottom);
    sideBottomLayout->addWidget(importButton);
    sideBottomLayout->addWidget(exportButton);
    sideLayout->addLayout(sideBottomLayout, 1, 0, Qt::AlignBottom);

    connect(addButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::addUser);
    connect(editButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::editUser);
    connect(deleteButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::deleteUser);
    connect(exportButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::usersExport);
    connect(importButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::usersImport);
    connect(usersTable, &QTableView::doubleClicked, this, &DashboardWidgetEmployee::findAccount);
    connect(accountWidget->currentContent, &AccountInfoLabel::doubleClicked, this,
            &DashboardWidgetEmployee::findRecords);
    connect(accountWidget->savingsContent, &AccountInfoLabel::doubleClicked, this,
            &DashboardWidgetEmployee::findRecords);
    connect(accountWidget, &AccountWidget::savingsRecordsFind, this, &DashboardWidgetEmployee::findRecords);

    usersLayout->addWidget(usersTable);
    usersLayout->addLayout(sideLayout);
    usersTab->setLayout(usersLayout);

    tabWidget->addTab(usersTab, "Users");

    auto accountTab = new QWidget;
    auto accountLayout = new QVBoxLayout;
    accountTab->setLayout(accountLayout);
    accountLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    accountLayout->addWidget(accountFinder);
    accountLayout->addLayout(accountWidget);

    connect(accountFinder, &DashBoardFinder::find, accountWidget, &AccountWidget::fetchByUserId);
    connect(recordFinder, &DashBoardFinder::find, this, &DashboardWidgetEmployee::fetchRecordsByAccountId);

    tabWidget->addTab(accountTab, "Account");

    auto recordTab = new QWidget;
    auto recordLayout = new QVBoxLayout;
    auto recordTableLayout = new QHBoxLayout;
    recordTab->setLayout(recordLayout);
    recordFinder->finder->setPlaceholderText("Account ID...");
    recordLayout->addWidget(recordFinder);

    auto recordsTableSelection = recordsTable->selectionModel();
    connect(recordsTableSelection, &QItemSelectionModel::selectionChanged, this,
            &DashboardWidgetEmployee::activateRedeemButton);
    connect(redeemButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::redeemFixedDeposit);


    auto recordsSideLayout = new QGridLayout;
    auto recordsSideTopLayout = new QVBoxLayout;
    recordsSideTopLayout->setAlignment(Qt::AlignTop);
    redeemButton->setEnabled(false);
    recordsSideTopLayout->addWidget(redeemButton);
    recordsSideLayout->addLayout(recordsSideTopLayout, 0, 0, Qt::AlignTop);

    recordTableLayout->addWidget(recordsTable);
    recordTableLayout->addLayout(recordsSideLayout);
    recordLayout->addLayout(recordTableLayout);
    recordLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    tabWidget->addTab(recordTab, "Records");

    auto configTab = new QWidget;
    auto configLayout = new QVBoxLayout;
    configLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    auto interestRate = Db::getStorage().get_all<Config>(where(c(&Config::key) == "interestRate"));
    interestRateLabel->setText(
            QString("Current interest rate for fixed deposit: %1").arg(interestRate.front().value.c_str()));
    configLayout->addWidget(interestRateLabel);
    configLayout->addWidget(interestButton);
    configTab->setLayout(configLayout);
    connect(interestButton, &QAbstractButton::clicked, this, &DashboardWidgetEmployee::setInterestRate);
    tabWidget->addTab(configTab, "Config");

    mainLayout->addWidget(tabWidget);

    auto copyright = new QLabel("Azure Bank™");
    copyright->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(copyright);
}

void DashboardWidgetEmployee::refreshUsersTable() {
    usersModelProxy->setSourceModel(usersModel);
    usersTable->setModel(usersModelProxy);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    usersTable->verticalHeader()->hide();
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setSortingEnabled(true);
    usersTable->sortByColumn(0, Qt::AscendingOrder);
    usersTable->setMinimumWidth(600);
}

void DashboardWidgetEmployee::refreshRecordsTable() {
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

void DashboardWidgetEmployee::activateButtons() {
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void DashboardWidgetEmployee::activateRedeemButton(const QItemSelection &selected, const QItemSelection &deselected) {
    auto recordsTableSelection = recordsTable->selectionModel();
    auto selectedRows = recordsTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto recordId = recordsModelProxy->data(row, Qt::EditRole).toInt();
    auto record = Db::getStorage().get<Record>(recordId);
    if (record.type == RecordType::FixedDeposit && !record.isRedeemed) {
        redeemButton->setEnabled(true);
    } else {
        redeemButton->setEnabled(false);
    }
}

void DashboardWidgetEmployee::addUser() {
    UserDialog userDialog{this, true};
    connect(&userDialog, &UserDialog::userAdded, this, &DashboardWidgetEmployee::userAdded);
    connect(&userDialog, &UserDialog::userAdded, usersModelProxy, &QSortFilterProxyModel::invalidate);

    userDialog.exec();
}

void DashboardWidgetEmployee::editUser() {
    auto usersTableSelection = usersTable->selectionModel();
    auto selectedRows = usersTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto uid = usersModelProxy->data(row, Qt::EditRole).toInt();
    UserDialog userDialog{this, Db::getStorage().get<User>(uid), true};
    connect(&userDialog, &UserDialog::userChanged, this, &DashboardWidgetEmployee::userChanged);
    connect(&userDialog, &UserDialog::userChanged, usersModelProxy, &QSortFilterProxyModel::invalidate);

    userDialog.exec();
}

void DashboardWidgetEmployee::deleteUser() {
    auto usersTableSelection = usersTable->selectionModel();
    auto selectedRows = usersTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto uid = usersModelProxy->data(row, Qt::EditRole).toInt();
    int ret = QMessageBox::warning(this, tr("Delete user - Azure Bank"),
                                   tr("Do you really want to delete the user?"),
                                   QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        // TODO: check accounts
        Db::getStorage().remove<User>(uid);
        usersModel->fetchData();
        usersModelProxy->invalidate();
    }
}

void DashboardWidgetEmployee::findAccount(const QModelIndex &index) {
    auto uid = usersModelProxy->data(index, Qt::EditRole).toInt();
    accountFinder->finder->setText(QString::number(uid));
    accountFinder->finderButton->click();
    tabWidget->setCurrentIndex(1);
}

void DashboardWidgetEmployee::findRecords(int accountId) {
    recordFinder->finder->setText(QString::number(accountId));
    recordFinder->finderButton->click();
    tabWidget->setCurrentIndex(2);
}

void DashboardWidgetEmployee::userChanged(User user) {
    Db::getStorage().update(user);
    usersModel->fetchData();
}

void DashboardWidgetEmployee::userAdded(User user) {
    Db::getStorage().insert(user);
    usersModel->fetchData();
}

void DashboardWidgetEmployee::usersExport() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Export users and associated accounts"), "",
                                                    tr("Database (*.db);;All Files (*)"));
    if (!fileName.isEmpty()) {
        if (QFile::exists(fileName)) QFile::remove(fileName);
        QFile::copy(QString(DB_FILE), fileName);
    }
}

void DashboardWidgetEmployee::usersImport() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        int ret = QMessageBox::information(this, tr("Import - Azure Bank"),
                                           tr("After importing you will need to restart."),
                                           QMessageBox::Yes | QMessageBox::Cancel);
        if (ret == QMessageBox::Yes) {
            QFile::remove(QString(DB_FILE).append(".bak"));
            QFile::rename(QString(DB_FILE), QString(DB_FILE).append(".bak"));
            QFile::copy(fileName, QString(DB_FILE));
            exit(0);
        }
    }
}

void DashboardWidgetEmployee::fetchRecordsByAccountId(int accountId) {
//    qDebug() << accountId;
    if (accountId == 0) {
        recordsModel->fetchData();
        recordsModelProxy->invalidate();
    } else {
        recordsModel->fetchDataByAccountId(accountId);
        recordsModelProxy->invalidate();
    }
}

void DashboardWidgetEmployee::setInterestRate() {
    bool ok;
    auto interestRate = Db::getStorage().get_all<Config>(where(c(&Config::key) == "interestRate")).front();
    double rate = QInputDialog::getDouble(nullptr, tr("Set Interest Rate - Azure Bank"),
                                          tr("New Interest Rate (won't affect existing fixed deposit): "),
                                          std::stod(interestRate.value), 0, 2147483647, 2, &ok);
    if (rate > 0 && ok) {
        interestRate.value = QString::number(rate, 'f', 2).toStdString();
        Db::getStorage().update(interestRate);
        interestRateLabel->setText(
                QString("Current interest rate for fixed deposit: %1").arg(interestRate.value.c_str()));
    }
}

void DashboardWidgetEmployee::redeemFixedDeposit() {
    auto recordsTableSelection = recordsTable->selectionModel();
    auto selectedRows = recordsTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto recordId = recordsModelProxy->data(row, Qt::EditRole).toInt();
    auto record = Db::getStorage().get<Record>(recordId);
    auto start = QDateTime::fromString(record.time.c_str(), "yyyy.MM.dd hh:mm:ss");
    auto end = QDateTime::currentDateTime();
    int seconds = start.secsTo(end);
    int interest = (double) record.amount * record.interestRate / 100 * ((double) seconds / 31536000);
//    qDebug() << interest;
    int ret = QMessageBox::information(nullptr, tr("Redeem - Azure Bank"),
                                       QString("After redeem you will get $%1 of interest, continue?").arg(
                                               QString::number((double) interest / 100, 'f', 2)),
                                       QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        accountWidget->getSavingsAccount().redeem(record, interest);
        fetchRecordsByAccountId(record.to);
        accountWidget->fetchByUserId(accountWidget->getUser().id);
        redeemButton->setEnabled(false);
    }
}
