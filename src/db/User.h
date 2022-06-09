#pragma once

#include <string>

#ifndef CPP_TERM_PROJECT_USER_H
#define CPP_TERM_PROJECT_USER_H

class User {
public:
    int id;
    std::string name;
    std::string idNumber;
    std::string phoneNumber;
    std::string password;
};

#endif //CPP_TERM_PROJECT_USER_H
