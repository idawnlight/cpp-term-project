#pragma once

#include <string>

#ifndef CPP_TERM_PROJECT_ACCOUNT_H
#define CPP_TERM_PROJECT_ACCOUNT_H

enum AccountType {
    Current,
    Savings
};

std::string AccountTypeToString(AccountType type);
std::unique_ptr<AccountType> AccountTypeFromString(const std::string& s);

class Account {
public:
    int id;
    int belong_to;
    int balance;
    AccountType type;
};

#endif //CPP_TERM_PROJECT_ACCOUNT_H
