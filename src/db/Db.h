#pragma once

#ifndef CPP_TERM_PROJECT_DB_H
#define CPP_TERM_PROJECT_DB_H

#include "sqlite_orm/sqlite_orm.h"
#include "User.h"
#include "Account.h"
#include "Record.h"
#include "Config.h"

using namespace sqlite_orm;

namespace sqlite_orm {

    /**
     *  First of all is a type_printer template class.
     *  It is responsible for sqlite type string representation.
     *  We want AccountType to be `TEXT` so let's just derive from
     *  text_printer. Also there are other printers: real_printer and
     *  integer_printer. We must use them if we want to map our type to `REAL` (double/float)
     *  or `INTEGER` (int/long/short etc) respectively.
     */
    template<>
    struct type_printer<AccountType> : public text_printer {
    };
    template<>
    struct type_printer<RecordType> : public text_printer {
    };

    /**
     *  This is a binder class. It is used to bind c++ values to sqlite queries.
     *  Here we have to create AccountType string representation and bind it as string.
     *  Any statement_binder specialization must have `int bind(sqlite3_stmt*, int, const T&)` function
     *  which returns bind result. Also you can call any of `sqlite3_bind_*` functions directly.
     *  More here https://www.sqlite.org/c3ref/bind_blob.html
     */
    template<>
    struct statement_binder<AccountType> {

        int bind(sqlite3_stmt *stmt, int index, const AccountType &value) {
            return statement_binder<std::string>().bind(stmt, index, AccountTypeToString(value));
            //  or return sqlite3_bind_text(stmt, index++, AccountTypeToString(value).c_str(), -1, SQLITE_TRANSIENT);
        }
    };

    template<>
    struct statement_binder<RecordType> {

        int bind(sqlite3_stmt *stmt, int index, const RecordType &value) {
            return statement_binder<std::string>().bind(stmt, index, RecordTypeToString(value));
            //  or return sqlite3_bind_text(stmt, index++, RecordTypeToString(value).c_str(), -1, SQLITE_TRANSIENT);
        }
    };

    /**
     *  field_printer is used in `dump` and `where` functions. Here we have to create
     *  a string from mapped object.
     */
    template<>
    struct field_printer<AccountType> {
        std::string operator()(const AccountType &t) const {
            return AccountTypeToString(t);
        }
    };

    template<>
    struct field_printer<RecordType> {
        std::string operator()(const RecordType &t) const {
            return RecordTypeToString(t);
        }
    };

    /**
     *  This is a reverse operation: here we have to specify a way to transform string received from
     *  database to our AccountType object. Here we call `AccountTypeFromString` and throw `std::runtime_error` if it returns
     *  nullptr. Every `row_extractor` specialization must have `extract(const char*)` and `extract(sqlite3_stmt *stmt,
     * int columnIndex)` functions which return a mapped type value.
     */
    template<>
    struct row_extractor<AccountType> {
        AccountType extract(const char *row_value) {
            if (auto AccountType = AccountTypeFromString(row_value)) {
                return *AccountType;
            } else {
                throw std::runtime_error("incorrect AccountType string (" + std::string(row_value) + ")");
            }
        }

        AccountType extract(sqlite3_stmt *stmt, int columnIndex) {
            auto str = sqlite3_column_text(stmt, columnIndex);
            return this->extract((const char *) str);
        }
    };

    template<>
    struct row_extractor<RecordType> {
        RecordType extract(const char *row_value) {
            if (auto RecordType = RecordTypeFromString(row_value)) {
                return *RecordType;
            } else {
                throw std::runtime_error("incorrect RecordType string (" + std::string(row_value) + ")");
            }
        }

        RecordType extract(sqlite3_stmt *stmt, int columnIndex) {
            auto str = sqlite3_column_text(stmt, columnIndex);
            return this->extract((const char *) str);
        }
    };
}

static const char *DB_FILE = "db.sqlite";

class Db {
public:
    static auto getStorage() {
        return make_storage(DB_FILE,
                            make_table("users",
                                       make_column("id", &User::id, autoincrement(), primary_key()),
                                       make_column("name", &User::name),
                                       make_column("idNumber", &User::idNumber, unique()),
                                       make_column("phoneNumber", &User::phoneNumber, unique()),
                                       make_column("password", &User::password),
                                       make_column("employeeId", &User::employeeId)),
                            make_table("accounts",
                                       make_column("id", &Account::id, autoincrement(), primary_key()),
                                       make_column("balance", &Account::balance),
                                       make_column("belong_to", &Account::belong_to),
                                       make_column("type", &Account::type)),
                            make_table("records",
                                       make_column("id", &Record::id, autoincrement(), primary_key()),
                                       make_column("amount", &Record::amount),
                                       make_column("from", &Record::from),
                                       make_column("to", &Record::to),
                                       make_column("type", &Record::type),
                                       make_column("isRedeemed", &Record::isRedeemed),
                                       make_column("interestRate", &Record::interestRate),
                                       make_column("remark", &Record::remark),
                                       make_column("time", &Record::time)),
                            make_table("config",
                                       make_column("id", &Config::id, autoincrement(), primary_key()),
                                       make_column("key", &Config::key),
                                       make_column("value", &Config::value)));
    }
};

#endif //CPP_TERM_PROJECT_DB_H
