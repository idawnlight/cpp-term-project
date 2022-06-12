//
// Created by 黎明余光 on 2022/6/12.
//

#include "AccountWidget.h"
#include "db/Db.h"

AccountWidget::AccountWidget(QWidget *parent, int userId, bool isEmployee) : QGridLayout(parent),
                                                                             isEmployee(isEmployee) {
    initWidget();
    try {
        user = Db::getStorage().get<User>(userId);
        fetchByUserId(user.id);
    } catch (std::exception e) {
        user = User();
//        qDebug() << user.id;
    }
}

AccountWidget::AccountWidget(QWidget *parent, User user, bool isEmployee) : QGridLayout(parent), user(user),
                                                                            isEmployee(isEmployee) {
    initWidget();
    fetchByUserId(user.id);
}

void AccountWidget::fetchByUserId(int userId) {
    try {
        current = Account();
        savings = Account();
        user = Db::getStorage().get<User>(userId);
        auto accounts = Db::getStorage().get_all<Account>(where(c(&Account::belong_to) == user.id));
        for (auto account: accounts) {
            if (account.type == AccountType::Current) {
                current = account;
            } else if (account.type == AccountType::Savings) {
                savings = account;
            }
        }
    } catch (std::exception e) {
        user = User();
//        qDebug() << user.id;
    }
    refreshWidget();
}

void AccountWidget::initWidget() {
    currentLayout->setAlignment(Qt::AlignTop);
    currentLabel->setAlignment(Qt::AlignTop);
    currentContent->setAlignment(Qt::AlignTop);
    currentLayout->addWidget(currentLabel);
    currentLayout->addWidget(currentContent);
    currentLayout->addWidget(currentDepositButton);
    currentLayout->addWidget(currentWithdrawnButton);
    currentLayout->addWidget(currentTransferButton);
    currentLayout->addWidget(openCurrentButton);
    currentLayout->addWidget(closeCurrentButton);

    savingsLayout->setAlignment(Qt::AlignTop);
    savingsLabel->setAlignment(Qt::AlignTop);
    savingsContent->setAlignment(Qt::AlignTop);
    savingsLayout->addWidget(savingsLabel);
    savingsLayout->addWidget(savingsContent);
    savingsLayout->addWidget(savingsDepositButton);
    savingsLayout->addWidget(savingsRedeemButton);
    savingsLayout->addWidget(openSavingsButton);
    savingsLayout->addWidget(closeSavingsButton);

    currentLabel->setVisible(false);
    savingsLabel->setVisible(false);
    currentDepositButton->setVisible(false);
    currentWithdrawnButton->setVisible(false);
    currentTransferButton->setVisible(false);

    savingsDepositButton->setVisible(false);
    savingsRedeemButton->setVisible(false);
    openCurrentButton->setVisible(false);
    closeCurrentButton->setVisible(false);
    openSavingsButton->setVisible(false);
    closeSavingsButton->setVisible(false);

    addWidget(topLabel, 0, 1, 1, 2);
    addLayout(currentLayout, 1, 1);
    addLayout(savingsLayout, 1, 2);
    setColumnStretch(0, 1);
    setColumnStretch(1, 1);
    setColumnStretch(2, 1);
    setColumnStretch(3, 1);

    connect(openCurrentButton, &QAbstractButton::clicked, this, &AccountWidget::openCurrentAccount);
    connect(closeCurrentButton, &QAbstractButton::clicked, this, &AccountWidget::closeCurrentAccount);
    connect(currentDepositButton, &QAbstractButton::clicked, this, &AccountWidget::currentAccountDeposit);
    connect(currentWithdrawnButton, &QAbstractButton::clicked, this, &AccountWidget::currentAccountWithdrawn);
    connect(currentTransferButton, &QAbstractButton::clicked, this, &AccountWidget::currentAccountTransfer);

    connect(openSavingsButton, &QAbstractButton::clicked, this, &AccountWidget::openSavingsAccount);
    connect(closeSavingsButton, &QAbstractButton::clicked, this, &AccountWidget::closeSavingsAccount);
    connect(savingsDepositButton, &QAbstractButton::clicked, this, &AccountWidget::savingsAccountDeposit);
    connect(savingsRedeemButton, &QAbstractButton::clicked, this, &AccountWidget::savingsAccountRedeem);
}

void AccountWidget::refreshWidget() {
    if (user.id == -1) {
        topLabel->setText("User not found");
        currentLabel->setVisible(false);
        savingsLabel->setVisible(false);
        currentContent->setVisible(false);
        savingsContent->setVisible(false);
    } else {
        topLabel->setText(QString("Account information of ").append(user.name.c_str()));
        currentLabel->setVisible(true);
        savingsLabel->setVisible(true);
        if (current.id == -1) {
            currentContent->setText("Current Account not opened.");
            currentDepositButton->setVisible(false);
            currentWithdrawnButton->setVisible(false);
            currentTransferButton->setVisible(false);
            if (isEmployee) {
                openCurrentButton->setVisible(true);
                closeCurrentButton->setVisible(false);
            }
        } else {
            currentContent->setAccount(current);
            currentDepositButton->setVisible(true);
            currentWithdrawnButton->setVisible(true);
            currentTransferButton->setVisible(true);
            if (isEmployee) {
                openCurrentButton->setVisible(false);
                closeCurrentButton->setVisible(true);
            }
        }
        if (savings.id == -1) {
            savingsContent->setText("Savings Account not opened.");
            savingsDepositButton->setVisible(false);
            savingsRedeemButton->setVisible(false);
            if (isEmployee) {
                openSavingsButton->setVisible(true);
                closeSavingsButton->setVisible(false);
            }
        } else {
            savingsContent->setAccount(savings);
            savingsDepositButton->setVisible(true);
            savingsRedeemButton->setVisible(true);
            if (isEmployee) {
                openSavingsButton->setVisible(false);
                closeSavingsButton->setVisible(true);
            }
        }
        currentContent->setVisible(true);
        savingsContent->setVisible(true);
    }
}

void AccountWidget::openCurrentAccount() {
    Account newAccount{user.id, AccountType::Current};
    Db::getStorage().insert(newAccount);

    fetchByUserId(user.id);
}

void AccountWidget::closeCurrentAccount() {
    if (current.balance != 0) {
        QMessageBox::information(nullptr, tr("Close Account - Azure Bank"),
                                 tr("You can't close an account with balance."),
                                 QMessageBox::Ok);
        return;
    }
    if (savings.id != -1) {
        QMessageBox::information(nullptr, tr("Close Account - Azure Bank"),
                                 tr("You can't close current account if savings account exists."),
                                 QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::warning(nullptr, tr("Close Account - Azure Bank"),
                                   tr("Do you really want to close the current account?"),
                                   QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        Db::getStorage().remove<Account>(current.id);
    }

    fetchByUserId(user.id);
}

void AccountWidget::openSavingsAccount() {
    Account newAccount{user.id, AccountType::Savings};
    Db::getStorage().insert(newAccount);

    fetchByUserId(user.id);
}

void AccountWidget::closeSavingsAccount() {
    if (savings.balance != 0) {
        QMessageBox::information(nullptr, tr("Close Account - Azure Bank"),
                                 tr("You can't close an account with balance."),
                                 QMessageBox::Ok);
        return;
    }
    int ret = QMessageBox::warning(nullptr, tr("Close Account - Azure Bank"),
                                   tr("Do you really want to close the savings account?"),
                                   QMessageBox::Yes | QMessageBox::Cancel);
    if (ret == QMessageBox::Yes) {
        Db::getStorage().remove<Account>(savings.id);
    }

    fetchByUserId(user.id);
}

void AccountWidget::currentAccountDeposit() {
    bool ok;
    double amount = QInputDialog::getDouble(nullptr, tr("Deposit - Azure Bank"),
                                            tr("Deposit Amount: "), 0, 0, 2147483647, 2, &ok);
    if (ok && amount > 0) {
        current.deposit(amount * 100);
        fetchByUserId(user.id);
        emit newRecord();
    }
}

void AccountWidget::currentAccountWithdrawn() {
    bool ok;
    double amount = QInputDialog::getDouble(nullptr, tr("Withdrawn - Azure Bank"),
                                            tr("Withdrawn Amount: "), 0, 0, (double) current.balance / 100, 2, &ok);
    if (ok && amount > 0) {
        current.withdrawn(amount * 100);
        fetchByUserId(user.id);
        emit newRecord();
    }
}

void AccountWidget::currentAccountTransfer() {
    bool ok;
    double receiver = QInputDialog::getInt(nullptr, tr("Transfer - Azure Bank"),
                                           tr("Receiver Account ID: "), 0, 0, (double) current.balance / 100, 1, &ok);
    if (ok && receiver != current.id) {
        if (auto account = Db::getStorage().get_pointer<Account>(receiver)) {
            if (account->type == AccountType::Savings) {
                QMessageBox::information(nullptr, tr("Transfer - Azure Bank"),
                                         tr("Transfer to savings account is not allowed.\nFor fixed deposit please use \"New Fixed Deposit\"."),
                                         QMessageBox::Ok);
                return;
            }
            double amount = QInputDialog::getDouble(nullptr, tr("Transfer - Azure Bank"),
                                                    QString("Transfer Amount (to %1): ").arg(
                                                            account->user().name.c_str()), 0, 0,
                                                    (double) current.balance / 100, 2, &ok);
            if (ok && amount > 0) {
                current.transfer(amount * 100, *account);
                fetchByUserId(user.id);
                emit newRecord();
            }
        } else {
            QMessageBox::information(nullptr, tr("Transfer - Azure Bank"),
                                     tr("Receiver account not found."),
                                     QMessageBox::Ok);
        }
    }
}

void AccountWidget::savingsAccountDeposit() {
    auto interestRate = Db::getStorage().get_all<Config>(where(c(&Config::key) == "interestRate")).front();
    bool ok;
    double amount = QInputDialog::getDouble(nullptr, tr("Fixed Deposit - Azure Bank"),
                                            QString("Fixed Deposit Amount (current interest rate %1): ").arg(
                                                    interestRate.value.c_str()), 0, 0, (double) current.balance / 100,
                                            2, &ok);
    if (ok && amount > 0) {
        savings.deposit(amount * 100, current, std::stod(interestRate.value));
        fetchByUserId(user.id);
        emit newRecord();
    }
}

void AccountWidget::savingsAccountRedeem() {
    emit savingsRecordsFind(savings.id);
}

Account AccountWidget::getSavingsAccount() {
    return savings;
}

User AccountWidget::getUser() {
    return user;
}
