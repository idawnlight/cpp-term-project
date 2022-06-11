#pragma once

#include <string>

#ifndef CPP_TERM_PROJECT_USER_H
#define CPP_TERM_PROJECT_USER_H

class User {
public:
    int id = -1;
    std::string name;
    std::string idNumber;
    std::string phoneNumber;
    std::string password;
    int employeeId = -1;

    User();
    User(std::string name, std::string idNumber, std::string phoneNumber, std::string password, bool isEmployee = false);
};

#endif //CPP_TERM_PROJECT_USER_H
