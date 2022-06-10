//
// Created by 黎明余光 on 2022/6/10.
//

#include "EmployeeWidget.h"

EmployeeWidget::EmployeeWidget(QWidget *parent, const User &user)
    : DashboardWidget(parent, user),
      usersModel(new UsersModel),
      usersTable(new QTableView),
      accountsTable(new QTableView) {
//    auto welcomeMsg = new QLabel(QString("Welcome back, <strong>") + user.name.c_str() + "</strong>");
//    mainLayout->addWidget(welcomeMsg);

    auto tabWidget = new QTabWidget;

    usersTable->setModel(usersModel);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    usersTable->verticalHeader()->hide();
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setSortingEnabled(true);
    usersTable->setMinimumWidth(600);

    auto usersTab = new QWidget;
    auto usersLayout = new QHBoxLayout();

    auto sideLayout = new QVBoxLayout;
    sideLayout->setAlignment(Qt::AlignTop);
    auto addButton = new QPushButton(tr("Add"));
    auto editButton = new QPushButton(tr("Edit"));
    auto deleteButton = new QPushButton(tr("Delete"));
    sideLayout->addWidget(addButton);
    sideLayout->addWidget(editButton);
    sideLayout->addWidget(deleteButton);

    usersLayout->addWidget(usersTable);
    usersLayout->addLayout(sideLayout);
    usersTab->setLayout(usersLayout);

    tabWidget->addTab(usersTab, "Users");

    mainLayout->addWidget(tabWidget);

    auto copyright = new QLabel("Azure Bank™");
    copyright->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(copyright);
}
