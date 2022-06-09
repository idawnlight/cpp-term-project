#include "Account.h"

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