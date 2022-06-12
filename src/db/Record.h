#pragma once

#ifndef CPP_TERM_PROJECT_RECORD_H
#define CPP_TERM_PROJECT_RECORD_H

#include <string>

enum RecordType {
    Deposit,
    Withdrawn,
    Transfer,
    FixedDeposit,
    RedeemFixedDeposit
};

std::string RecordTypeToString(RecordType type);
std::unique_ptr<RecordType> RecordTypeFromString(const std::string& s);

class Record {
public:
    int id;
    int amount;
    int from;
    int to;
    RecordType type;
    bool isRedeemed = false;
    double interestRate = 0;
    std::string remark;
    std::string time;

    Record();
    Record(RecordType type, int amount, int from = -1, int to = -1, double interestRate = 0);
};


#endif //CPP_TERM_PROJECT_RECORD_H
