#include "DashboardWidget.h"
#include "UserDialog.h"
#include <QtWidgets>

DashboardWidget::DashboardWidget(QWidget *parent, const User& user)
    : QWidget(parent),
      user(user),
      mainLayout(new QVBoxLayout) {
    auto headerLayout = new QHBoxLayout;
    auto welcomeMsg = new QLabel(QString("Welcome back, <strong>") + user.name.c_str() + "</strong>");
    headerLayout->addWidget(welcomeMsg);

    auto userInfoButton = new QPushButton(tr("Info..."));
    headerLayout->addWidget(userInfoButton, 0, Qt::AlignRight);
    connect(userInfoButton, &QAbstractButton::clicked, this, &DashboardWidget::userInfo);

    mainLayout->addLayout(headerLayout);

    setLayout(mainLayout);
}

void DashboardWidget::userInfo() {
    UserDialog userDialog{this, user, false};
    userDialog.exec();
}