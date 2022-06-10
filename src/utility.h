#pragma once

#include "sodium.h"

#include <cstring>
#include <string>
#include <iostream>

namespace Utility {
    void init();

    std::string password_hash(const char *password);

    bool password_verify(const char *password, const char *hashed_password);
};