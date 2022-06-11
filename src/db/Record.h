#pragma once

#ifndef CPP_TERM_PROJECT_RECORD_H
#define CPP_TERM_PROJECT_RECORD_H

#include <string>

enum RecordType {
    Deposit,
    Withdrawn,
    Transfer,
    FixedDeposit
};

std::string RecordTypeToString(RecordType type);
std::unique_ptr<RecordType> RecordTypeFromString(const std::string& s);

class Record {
public:
    int id;
    int amount;
    std::string from;
    std::string to;
    RecordType type;
    bool isRedeemed = false;
    double interestRate = 0;
    std::string remark;
    std::string time;
};


#endif //CPP_TERM_PROJECT_RECORD_H
