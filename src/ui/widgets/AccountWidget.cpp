//
// Created by 黎明余光 on 2022/6/12.
//

#include "AccountWidget.h"
#include "db/Db.h"

AccountWidget::AccountWidget(QWidget *parent, int userId) : QGridLayout(parent) {
    initWidget(false);
    try {
        user = Db::getStorage().get<User>(userId);
        fetchByUserId(user.id);
    } catch (std::exception e) {
        user = User();
        qDebug() << user.id;
    }
}

AccountWidget::AccountWidget(QWidget *parent, User user) : QGridLayout(parent), user(user) {
    initWidget();
    fetchByUserId(user.id);
}

void AccountWidget::fetchByUserId(int userId) {
    try {
        user = Db::getStorage().get<User>(userId);
        auto accounts = Db::getStorage().get_all<Account>(where(c(&Account::belong_to) == user.id));
        for (auto account : accounts) {
            if (account.type == AccountType::Current) {
                current = account;
            } else if (account.type == AccountType::Savings) {
                savings = account;
            }
        }
    } catch (std::exception e) {
        user = User();
        qDebug() << user.id;
    }
    refreshWidget();
}

void AccountWidget::initWidget(bool showNotFound) {
    currentLayout->addWidget(currentLabel);
    currentLayout->addWidget(currentContent);
    currentLayout->addWidget(openCurrentButton);
    currentLayout->addWidget(closeCurrentButton);

    savingLayout->addWidget(savingLabel);
    savingLayout->addWidget(savingContent);
    savingLayout->addWidget(openSavingButton);
    savingLayout->addWidget(closeSavingButton);

    currentLabel->setVisible(false);
    savingLabel->setVisible(false);
    openCurrentButton->setVisible(false);
    closeCurrentButton->setVisible(false);
    openSavingButton->setVisible(false);
    closeSavingButton->setVisible(false);

    addWidget(topLabel, 0, 0, 1, 2);
    addLayout(currentLayout, 1, 0);
    addLayout(savingLayout, 1, 1);
}


void AccountWidget::refreshWidget() {
    if (user.id == -1) {
        topLabel->setText("User not found");
        currentLabel->setVisible(false);
        savingLabel->setVisible(false);
        currentContent->setVisible(false);
        savingContent->setVisible(false);
    } else {
        topLabel->setText(QString("Account information of ").append(user.name.c_str()));
        currentLabel->setVisible(true);
        savingLabel->setVisible(true);
        if (current.id == -1) {
            currentContent->setText("Current Account not opened.");
            openCurrentButton->setVisible(true);
            closeCurrentButton->setVisible(false);
        } else {
            currentContent->setText("Some Info.");
            openCurrentButton->setVisible(false);
            closeCurrentButton->setVisible(true);
        }
        if (savings.id == -1) {
            savingContent->setText("Savings Account not opened.");
            openSavingButton->setVisible(true);
            closeSavingButton->setVisible(false);
        } else {
            savingContent->setText("Some Info.");
            openSavingButton->setVisible(false);
            closeSavingButton->setVisible(true);
        }
        currentContent->setVisible(true);
        savingContent->setVisible(true);
    }
}
