#include "DashboardWidget.h"
#include "UserDialog.h"
#include "db/Db.h"
#include <QtWidgets>

DashboardWidget::DashboardWidget(QWidget *parent, const User &user)
        : QWidget(parent),
          user(user),
          mainLayout(new QVBoxLayout) {
    auto headerLayout = new QHBoxLayout;
    auto welcomeMsg = new QLabel(QString("Welcome back, <strong>") + user.name.c_str() + "</strong>");
    headerLayout->addWidget(welcomeMsg);

    auto buttonLayout = new QHBoxLayout;

    auto logOutButton = new QPushButton(tr("Log Out"));
//    headerLayout->addWidget(logOutButton, 0, Qt::AlignRight);
    auto userInfoButton = new QPushButton(tr("Info..."));
//    headerLayout->addWidget(userInfoButton, 0, Qt::AlignRight);

    connect(logOutButton, &QAbstractButton::clicked, this, &DashboardWidget::logOut);
    connect(userInfoButton, &QAbstractButton::clicked, this, &DashboardWidget::userInfo);

    buttonLayout->addWidget(logOutButton, 1, Qt::AlignRight);
    buttonLayout->addWidget(userInfoButton, 0, Qt::AlignRight);
    headerLayout->addLayout(buttonLayout);

    mainLayout->addLayout(headerLayout);

    setLayout(mainLayout);
}

void DashboardWidget::userInfo() {
    UserDialog userDialog{this, user, false};
    connect(&userDialog, &UserDialog::userChanged, this, &DashboardWidget::userChanged);
    userDialog.exec();
}

void DashboardWidget::userChanged(User user) {
    Db::getStorage().update(user);
}
