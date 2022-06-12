#include "Account.h"
#include "Record.h"
#include "Db.h"

std::string AccountTypeToString(AccountType type) {
    switch (type) {
        case AccountType::Current:
            return "current";
        case AccountType::Savings:
            return "savings";
    }
    throw std::domain_error("Invalid AccountType enum");
}

std::unique_ptr<AccountType> AccountTypeFromString(const std::string& s) {
    if (s == "current") {
        return std::make_unique<AccountType>(AccountType::Current);
    } else if (s == "savings") {
        return std::make_unique<AccountType>(AccountType::Savings);
    }
    return nullptr;
}

Account::Account() = default;

Account::Account(int belong_to, AccountType type) : belong_to(belong_to), type(type) {
    // TODO: duplication
    id = -1;
    balance = 0;
}

QString Account::toString() {
    QString msg;
    msg.append(QString("Account ID: <strong>") + QString::number(id) + QString("</strong>"));
    msg.append(QString("<br>Balance: <strong>") + QString::number((double) balance / 100, 'f', 2) + QString("</strong>"));
    return msg;
}

void Account::deposit(int amount) {
    if (type == AccountType::Current) {
        Record newRecord{RecordType::Deposit, amount, -1, id};
        Db::getStorage().insert(newRecord);
        balance += amount;
        Db::getStorage().update(*this);
    }
}

void Account::withdrawn(int amount) {
    if (type == AccountType::Current) {
        Record newRecord{RecordType::Withdrawn, amount, -1, id};
        Db::getStorage().insert(newRecord);
        balance -= amount;
        Db::getStorage().update(*this);
    }
}

void Account::transfer(int amount, Account receiver) {
    Record newRecord{RecordType::Transfer, amount, id, receiver.id};
    Db::getStorage().insert(newRecord);
    balance -= amount;
    receiver.balance += amount;
    Db::getStorage().update(*this);
    Db::getStorage().update(receiver);
}

User Account::user() {
    if (id == -1) {
        return User();
    } else {
        return Db::getStorage().get<User>(belong_to);
    }
}
