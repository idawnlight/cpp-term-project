//
// Created by 黎明余光 on 2022/6/7.
//

#include <QDateTime>
#include "Record.h"

std::string RecordTypeToString(RecordType type) {
    switch (type) {
        case RecordType::Deposit:
            return "deposit";
        case RecordType::Withdrawn:
            return "withdrawn";
        case RecordType::Transfer:
            return "transfer";
        case RecordType::FixedDeposit:
            return "fixed_deposit";
        case RecordType::RedeemFixedDeposit:
            return "redeem_fixed_deposit";
    }
    throw std::domain_error("Invalid RecordType enum");
}

std::unique_ptr<RecordType> RecordTypeFromString(const std::string &s) {
    if (s == "deposit") {
        return std::make_unique<RecordType>(RecordType::Deposit);
    } else if (s == "withdrawn") {
        return std::make_unique<RecordType>(RecordType::Withdrawn);
    } else if (s == "transfer") {
        return std::make_unique<RecordType>(RecordType::Transfer);
    } else if (s == "fixed_deposit") {
        return std::make_unique<RecordType>(RecordType::FixedDeposit);
    } else if (s == "redeem_fixed_deposit") {
        return std::make_unique<RecordType>(RecordType::RedeemFixedDeposit);
    }
    return nullptr;
}

Record::Record() = default;

Record::Record(RecordType type, int amount, int from, int to, double interestRate)
        : amount(amount),
          from(from),
          to(to),
          type(type),
          interestRate(interestRate) {
    id = -1;
    QDateTime current = QDateTime::currentDateTime();
    time = current.toString("yyyy.MM.dd hh:mm:ss").toStdString();
}
