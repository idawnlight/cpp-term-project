#pragma once

#include "sodium.h"

#include <cstring>
#include <string>
#include <iostream>

class Utility {
public:
    static void init();

    static std::string password_hash(const char *password);

    static bool password_verify(const char *password, const char *hashed_password);

    static bool checkIdNumber(const char *idNumber);

    static bool checkPhoneNumber(const char *phoneNumber);
};