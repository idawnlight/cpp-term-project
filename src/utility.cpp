#include "utility.h"
#include "db/Db.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

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

bool Utility::checkIdNumber(const char *idNumber) {
    QRegularExpression rx("([1-6][1-9]|50)\\d{4}(18|19|20)\\d{2}((0[1-9])|10|11|12)(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]");
    QRegularExpressionValidator v(rx, 0);
    auto str = QString::fromLocal8Bit(idNumber);
    int pos = 0;
    if (!v.validate(str, pos)) return false;

    int q[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    std::string symbol = "10X98765432";
    int z = 0;
    for (int j = 0; j < 17; j++) {
        z += (idNumber[j] - '0') * q[j];
    }
    z %= 11;
//    qDebug() << symbol[z];
    return symbol[z] == idNumber[17];
}

bool Utility::checkPhoneNumber(const char *phoneNumber) {
    QRegularExpression rx("1[3456789]\\d{9}");
    QRegularExpressionValidator v(rx, 0);
    auto str = QString::fromLocal8Bit(phoneNumber);
    int pos = 0;
    return v.validate(str, pos);
}
