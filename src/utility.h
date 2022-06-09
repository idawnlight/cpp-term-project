#pragma once

#include "sodium.h"

#include <cstring>
#include <string>
#include <iostream>

namespace Utility {
    void init() {
        if (sodium_init() == -1) {
            /* TODO: error */
        }
    }

    std::string password_hash(const char *password) {
        char hashed_password[crypto_pwhash_STRBYTES];

        if (crypto_pwhash_str
                    (hashed_password, password, strlen(password),
                     crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
            /* TODO: out of memory */
        }

        return hashed_password;
    }

    bool password_verify(const char *password, const char *hashed_password) {
        if (crypto_pwhash_str_verify
                    (hashed_password, password, strlen(password)) != 0) {
            return false;
            /* TODO: out of memory */
        }

        return true;
    }
};