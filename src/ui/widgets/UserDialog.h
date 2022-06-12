//
// Created by 黎明余光 on 2022/6/10.
//

#ifndef CPP_TERM_PROJECT_USERDIALOG_H
#define CPP_TERM_PROJECT_USERDIALOG_H


#include <QDialog>
#include <QtWidgets>

#include "db/User.h"

enum UserDialogType {
    Add,
    Edit
};

class UserDialog : public QDialog {
Q_OBJECT
public:
    explicit UserDialog(QWidget *parent = nullptr, User user = User{}, bool isEditable = false);

    explicit UserDialog(QWidget *parent = nullptr, bool addUser = true);

public slots:

    void accept() override;

signals:

    void userAdded(User user);

    void userChanged(User user);

private:
    User user;
    bool isEditable;
    UserDialogType type;
    QLineEdit *nameText = new QLineEdit;
    QLineEdit *passwordText = new QLineEdit;
    QLineEdit *idNumText = new QLineEdit;
    QLineEdit *phoneNumText = new QLineEdit;
    QGridLayout *gLayout = new QGridLayout;

    void initDialog();
};


#endif //CPP_TERM_PROJECT_USERDIALOG_H
