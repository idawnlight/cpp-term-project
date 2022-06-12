//
// Created by 黎明余光 on 2022/6/12.
//

#ifndef CPP_TERM_PROJECT_ACCOUNTWIDGET_H
#define CPP_TERM_PROJECT_ACCOUNTWIDGET_H

#include "db/Account.h"
#include "db/User.h"
#include "AccountInfoLabel.h"

#include <QtWidgets>

class AccountWidget : public QGridLayout {
Q_OBJECT
public:
    AccountWidget(QWidget *parent = nullptr, int userId = -1, bool isEmployee = true);

    AccountWidget(QWidget *parent = nullptr, User user = {}, bool isEmployee = false);

    AccountInfoLabel *currentContent = new AccountInfoLabel();
    AccountInfoLabel *savingsContent = new AccountInfoLabel();

    Account getSavingsAccount();

    User getUser();

public slots:

    void fetchByUserId(int userId);
    void openCurrentAccount();
    void closeCurrentAccount();
    void currentAccountDeposit();
    void currentAccountWithdrawn();
    void currentAccountTransfer();
    void savingsAccountDeposit();
    void savingsAccountRedeem();
    void openSavingsAccount();
    void closeSavingsAccount();

signals:

    void savingsRecordsFind(int accountId);
    void newRecord();

private:
    User user;
    Account current;
    Account savings;
    bool isEmployee = true;
    QLabel *topLabel = new QLabel();
    QVBoxLayout *currentLayout = new QVBoxLayout;
    QVBoxLayout *savingsLayout = new QVBoxLayout;
    QLabel *currentLabel = new QLabel("<h2>Current</h2>");
    QLabel *savingsLabel = new QLabel("<h2>Savings</h2>");

    QPushButton *currentDepositButton = new QPushButton(tr("Deposit"));
    QPushButton *currentWithdrawnButton = new QPushButton(tr("Withdrawn"));
    QPushButton *currentTransferButton = new QPushButton(tr("Transfer"));

    QPushButton *savingsDepositButton = new QPushButton(tr("New Fixed Deposit"));
    QPushButton *savingsRedeemButton = new QPushButton(tr("Redeem Fixed Deposit"));

    QPushButton *openCurrentButton = new QPushButton(tr("Open Current Account"));
    QPushButton *openSavingsButton = new QPushButton(tr("Open Savings Account"));
    QPushButton *closeCurrentButton = new QPushButton(tr("Close Current Account"));
    QPushButton *closeSavingsButton = new QPushButton(tr("Close Savings Account"));

    void initWidget();

    void refreshWidget();

};

#endif //CPP_TERM_PROJECT_ACCOUNTWIDGET_H
