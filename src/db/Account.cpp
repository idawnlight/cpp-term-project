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

std::unique_ptr<AccountType> AccountTypeFromString(const std::string &s) {
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
    msg.append(
            QString("<br>Balance: <strong>") + QString::number((double) balance / 100, 'f', 2) + QString("</strong>"));
    return msg;
}

void Account::deposit(int amount, Account from, double interestRate) {
    if (type == AccountType::Current) {
        Record newRecord{RecordType::Deposit, amount, -1, id};
        Db::getStorage().insert(newRecord);
        balance += amount;
        Db::getStorage().update(*this);
    } else {
        Record newRecord{RecordType::FixedDeposit, amount, from.id, id, interestRate};
        Db::getStorage().insert(newRecord);
        balance += amount;
        from.balance -= amount;
        Db::getStorage().update(*this);
        Db::getStorage().update(from);
    }
}

void Account::withdrawn(int amount) {
    if (type == AccountType::Current) {
        Record newRecord{RecordType::Withdrawn, amount, id, -1};
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

void Account::redeem(Record record, int interest) {
    Record redeemRecord{RecordType::RedeemFixedDeposit, record.amount, record.to, record.from};
    Record interestRecord{RecordType::RedeemFixedDeposit, interest, -1, record.from};
    auto current = Db::getStorage().get<Account>(record.from);
    balance -= record.amount;
    current.balance += record.amount;
    current.balance += interest;
    Db::getStorage().update(*this);
    Db::getStorage().update(current);
    record.isRedeemed = true;
    Db::getStorage().update(record);
    Db::getStorage().insert(redeemRecord);
    Db::getStorage().insert(interestRecord);
}

User Account::user() {
    if (id == -1) {
        return User();
    } else {
        return Db::getStorage().get<User>(belong_to);
    }
}
