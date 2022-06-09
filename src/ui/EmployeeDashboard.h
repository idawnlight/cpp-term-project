#include <QMainWindow>
#include "db/Employee.h"

#ifndef CPP_TERM_PROJECT_EMPLOYEEDASHBOARD_H
#define CPP_TERM_PROJECT_EMPLOYEEDASHBOARD_H


class EmployeeDashboard : public QMainWindow {
    Q_OBJECT

public slots:
    void setUser(Employee employee);

};


#endif //CPP_TERM_PROJECT_EMPLOYEEDASHBOARD_H
