#include "utility.h"
#include "db/Db.h"

void Utility::init() {
    Db::getStorage().sync_schema();
    if (sodium_init() == -1) {
        /* TODO: error */
    }
}

std::string Utility::password_hash(const char *password) {
    char hashed_password[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str
                (hashed_password, password, strlen(password),
                 crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        /* TODO: out of memory */
    }

    return hashed_password;
}

bool Utility::password_verify(const char *password, const char *hashed_password) {
    if (crypto_pwhash_str_verify
                (hashed_password, password, strlen(password)) != 0) {
        return false;
        /* TODO: out of memory */
    }

    return true;
}
