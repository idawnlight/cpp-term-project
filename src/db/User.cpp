#include "User.h"
#include "Db.h"

#include <utility>

User::User() = default;

User::User(std::string name, std::string idNumber, std::string phoneNumber, std::string password, bool isEmployee)
: name(std::move(name)), idNumber(std::move(idNumber)), phoneNumber(std::move(phoneNumber)), password(std::move(password))
{
    id = -1;
    if (isEmployee) {
        auto employee = Db::getStorage().get_all<User>(where(c(&User::employeeId) >= 0), order_by(&User::employeeId).desc());
        if (employee.size() == 0) {
            employeeId = 1;
        } else {
            employeeId = employee.front().employeeId + 1;
        }
    } else {
        employeeId = -1;
    }
}
