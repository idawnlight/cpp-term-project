//
// Created by 黎明余光 on 2022/6/10.
//

#include "EmployeeWidget.h"
#include "UserDialog.h"
#include "db/Db.h"

EmployeeWidget::EmployeeWidget(QWidget *parent, const User &user)
    : DashboardWidget(parent, user),
      usersModel(new UsersModel),
      usersTable(new QTableView),
      accountsTable(new QTableView) {
//    auto welcomeMsg = new QLabel(QString("Welcome back, <strong>") + user.name.c_str() + "</strong>");
//    mainLayout->addWidget(welcomeMsg);

    auto tabWidget = new QTabWidget;
    refreshTable();

    auto usersTableSelection = usersTable->selectionModel();
    connect(usersTableSelection, &QItemSelectionModel::selectionChanged, this, &EmployeeWidget::activateButtons);

    auto usersTab = new QWidget;
    auto usersLayout = new QHBoxLayout();

    auto sideLayout = new QVBoxLayout;
    sideLayout->setAlignment(Qt::AlignTop);
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    sideLayout->addWidget(addButton);
    sideLayout->addWidget(editButton);
    sideLayout->addWidget(deleteButton);

    connect(addButton, &QAbstractButton::clicked, this, &EmployeeWidget::addUser);
    connect(editButton, &QAbstractButton::clicked, this, &EmployeeWidget::editUser);
    connect(deleteButton, &QAbstractButton::clicked, this, &EmployeeWidget::deleteUser);

    usersLayout->addWidget(usersTable);
    usersLayout->addLayout(sideLayout);
    usersTab->setLayout(usersLayout);

    tabWidget->addTab(usersTab, "Users");

    mainLayout->addWidget(tabWidget);

    auto copyright = new QLabel("Azure Bank™");
    copyright->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(copyright);
}

void EmployeeWidget::refreshTable() {
    proxyModel->setSourceModel(usersModel);
    usersTable->setModel(proxyModel);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    usersTable->verticalHeader()->hide();
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setSortingEnabled(true);
    usersTable->sortByColumn(0, Qt::AscendingOrder);
    usersTable->setMinimumWidth(600);
}

void EmployeeWidget::activateButtons() {
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void EmployeeWidget::addUser() {
    UserDialog userDialog{this, true};
    connect(&userDialog, &UserDialog::userAdded, this, &EmployeeWidget::userAdded);
    connect(&userDialog, &UserDialog::userAdded, proxyModel, &QSortFilterProxyModel::invalidate);

    userDialog.exec();
}

void EmployeeWidget::editUser() {
    auto usersTableSelection = usersTable->selectionModel();
    auto selectedRows = usersTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto uid = proxyModel->data(row, Qt::EditRole).toInt();
    UserDialog userDialog{this, Db::getStorage().get<User>(uid), true};
    connect(&userDialog, &UserDialog::userChanged, this, &EmployeeWidget::userChanged);
    connect(&userDialog, &UserDialog::userChanged, proxyModel, &QSortFilterProxyModel::invalidate);

    userDialog.exec();
}

void EmployeeWidget::deleteUser() {
    auto usersTableSelection = usersTable->selectionModel();
    auto selectedRows = usersTableSelection->selectedRows();
    auto row = selectedRows.front();
    auto uid = proxyModel->data(row, Qt::EditRole).toInt();
    int ret = QMessageBox::warning(this, tr("Delete user - Azure Bank"),
                                   tr("Do you really want to delete the user?"),
                                   QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        // TODO: check accounts
        Db::getStorage().remove<User>(uid);
        usersModel->fetchData();
        proxyModel->invalidate();
    }
}

void EmployeeWidget::userChanged(User user) {
//    std::vector<User> temp;
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
//    temp.push_back(User {"Light", "440102198001021230", "13700000000", "password"});
    Db::getStorage().update(user);
    usersModel->fetchData();
//    proxyModel->invalidate();
}

void EmployeeWidget::userAdded(User user) {
    Db::getStorage().insert(user);
    usersModel->fetchData();
}
