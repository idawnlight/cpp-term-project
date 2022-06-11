#include "DashboardWidgetEmployee.h"
#include "UserDialog.h"
#include "db/Db.h"

DashboardWidgetEmployee::DashboardWidgetEmployee(QWidget *parent, const User &user)
    : DashboardWidget(parent, user),
      usersModel(new UsersModel),
      usersTable(new QTableView),
      accountsTable(new QTableView) {
//    auto welcomeMsg = new QLabel(QString("Welcome back, <strong>") + user.name.c_str() + "</strong>");
//    mainLayout->addWidget(welcomeMsg);

    auto tabWidget = new QTabWidget;
    refreshTable();

    auto usersTableSelection = usersTable->selectionModel();
    connect(usersTableSelection, &QItemSelectionModel::selectionChanged, this, &DashboardWidgetEmployee::activateButtons);

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

    tabWidget->addTab(accountTab, "Account");

    auto recordTab = new QWidget;
    auto recordLayout = new QVBoxLayout;
    recordTab->setLayout(recordLayout);
    recordLayout->addWidget(recordFinder);
    recordLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    tabWidget->addTab(recordTab, "Records");

    mainLayout->addWidget(tabWidget);

    auto copyright = new QLabel("Azure Bank™");
    copyright->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(copyright);
}

void DashboardWidgetEmployee::refreshTable() {
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

void DashboardWidgetEmployee::activateButtons() {
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
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

void DashboardWidgetEmployee::userChanged(User user) {
//    std::vector<User> temp;
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
    Db::getStorage().update(user);
    usersModel->fetchData();
//    usersModelProxy->invalidate();
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