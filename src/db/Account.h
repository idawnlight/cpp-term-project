#pragma once

#include <string>
#include <QString>
#include "User.h"
#include "Record.h"

#ifndef CPP_TERM_PROJECT_ACCOUNT_H
#define CPP_TERM_PROJECT_ACCOUNT_H

enum AccountType {
    Current,
    Savings
};

std::string AccountTypeToString(AccountType type);

std::unique_ptr<AccountType> AccountTypeFromString(const std::string &s);

class Account {
public:
    int id = -1;
    int belong_to;
    int balance;
    AccountType type;

    Account();

    Account(int belong_to, AccountType type);

    QString toString();

    void deposit(int amount, Account from = Account{}, double interestRate = 0);

    void withdrawn(int amount);

    void transfer(int amount, Account receiver);

    void redeem(Record record, int interest);

    User user();
};

#endif //CPP_TERM_PROJECT_ACCOUNT_H
