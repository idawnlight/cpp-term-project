#include <QMainWindow>
#include "db/User.h"

#ifndef CPP_TERM_PROJECT_USERDASHBOARD_H
#define CPP_TERM_PROJECT_USERDASHBOARD_H

class UserDashboard : public QMainWindow {
    Q_OBJECT

public slots:
    void setUser(User user);

};


#endif //CPP_TERM_PROJECT_USERDASHBOARD_H
