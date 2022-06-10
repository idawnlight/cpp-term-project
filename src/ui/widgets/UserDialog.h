//
// Created by 黎明余光 on 2022/6/10.
//

#ifndef CPP_TERM_PROJECT_USERDIALOG_H
#define CPP_TERM_PROJECT_USERDIALOG_H


#include <QDialog>
#include <QtWidgets>

#include "db/User.h"

class UserDialog : public QDialog {
    Q_OBJECT
public:
    explicit UserDialog(QWidget *parent = nullptr, User user = User{}, bool isEditable = false);

private:
    User user;
    bool isEditable;
    QLineEdit *nameText = new QLineEdit;
    QLineEdit *passwordText = new QLineEdit;
    QLineEdit *idNumText = new QLineEdit;
    QLineEdit *phoneNumText = new QLineEdit;

};


#endif //CPP_TERM_PROJECT_USERDIALOG_H
