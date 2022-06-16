#include "UserDialog.h"
#include "utility.h"
#include "db/Db.h"

UserDialog::UserDialog(QWidget *parent, bool addUser) : QDialog(parent), isEditable(true), type(UserDialogType::Add) {
    initDialog();
    setWindowTitle(tr("Add User - Rhine Bank"));

    gLayout->addWidget(new QLabel("Add a new user"), 0, 0, 1, 2);
}

UserDialog::UserDialog(QWidget *parent, User tUser, bool isEditable)
        : QDialog(parent),
          user(tUser),
          isEditable(isEditable),
          type(UserDialogType::Edit) {
    initDialog();
    setWindowTitle(tr("Edit User - Rhine Bank"));

    gLayout->addWidget(new QLabel("User ID"), 0, 0);
    gLayout->addWidget(new QLabel(QString::number(user.id)), 0, 1);
    nameText->setText(QString(user.name.c_str()));
    passwordText->setPlaceholderText("Leave blank to keep original password.");
    idNumText->setText(QString(user.idNumber.c_str()));
    phoneNumText->setText(QString(user.phoneNumber.c_str()));

    if (user.employeeId != -1) {
        gLayout->addWidget(new QLabel("Employee ID"), 5, 0);
        gLayout->addWidget(new QLabel(QString::number(user.employeeId)), 5, 1);
    }
}

void UserDialog::accept() {
    if (type == UserDialogType::Edit) {
        if (nameText->text() != user.name.c_str()) {
            user.name = nameText->text().toStdString();
        }
        if (idNumText->text() != user.idNumber.c_str()) {
            if (!Utility::checkIdNumber(idNumText->text().toLocal8Bit().data())) {
                QMessageBox::information(nullptr, tr("Edit User - Rhine Bank"),
                                         tr("The ID card number is invalid."),
                                         QMessageBox::Ok);
                return;
            }
            if (Db::getStorage().count<User>(where(c(&User::idNumber) == idNumText->text().toStdString())) != 0) {
                QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                         tr("The ID card number is registered."),
                                         QMessageBox::Ok);
                return;
            }
            user.idNumber = idNumText->text().toStdString();
        }
        if (phoneNumText->text() != user.phoneNumber.c_str()) {
            if (!Utility::checkPhoneNumber(phoneNumText->text().toLocal8Bit().data())) {
                QMessageBox::information(nullptr, tr("Edit User - Rhine Bank"),
                                         tr("The phone number is invalid."),
                                         QMessageBox::Ok);
                return;
            }
            if (Db::getStorage().count<User>(where(c(&User::phoneNumber) == phoneNumText->text().toStdString())) != 0) {
                QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                         tr("The phone number is registered."),
                                         QMessageBox::Ok);
                return;
            }
            user.phoneNumber = phoneNumText->text().toStdString();
        }
        if (!passwordText->text().isEmpty()) {
            user.password = Utility::password_hash(passwordText->text().toLocal8Bit().data());
        }

        emit userChanged(user);
    } else {
        if (nameText->text().isEmpty() || passwordText->text().isEmpty() || phoneNumText->text().isEmpty()) {
            QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                     tr("Please fill all the fields."),
                                     QMessageBox::Ok);
            return;
        }

        if (!Utility::checkIdNumber(idNumText->text().toLocal8Bit().data())) {
            QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                     tr("The ID card number is invalid."),
                                     QMessageBox::Ok);
            return;
        }
        if (Db::getStorage().count<User>(where(c(&User::idNumber) == idNumText->text().toStdString())) != 0) {
            QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                     tr("The ID card number is registered."),
                                     QMessageBox::Ok);
            return;
        }

        if (!Utility::checkPhoneNumber(phoneNumText->text().toLocal8Bit().data())) {
            QMessageBox::information(nullptr, tr("Edit User - Rhine Bank"),
                                     tr("The phone number is invalid."),
                                     QMessageBox::Ok);
            return;
        }
        if (Db::getStorage().count<User>(where(c(&User::phoneNumber) == phoneNumText->text().toStdString())) != 0) {
            QMessageBox::information(nullptr, tr("New User - Rhine Bank"),
                                     tr("The phone number is registered."),
                                     QMessageBox::Ok);
            return;
        }

        User newUser{nameText->text().toStdString(),
                     idNumText->text().toStdString(),
                     phoneNumText->text().toStdString(),
                     Utility::password_hash(passwordText->text().toLocal8Bit().data())};

        emit userAdded(newUser);
    }

    QDialog::accept();
}

void UserDialog::initDialog() {
    auto mainLayout = new QVBoxLayout;

    gLayout->setColumnMinimumWidth(1, 270);

    if (!isEditable) {
        nameText->setReadOnly(true);
        idNumText->setReadOnly(true);
        phoneNumText->setReadOnly(true);
    }

    gLayout->addWidget(new QLabel("Name"), 1, 0);
    gLayout->addWidget(nameText, 1, 1);

    gLayout->addWidget(new QLabel("Password"), 2, 0);
    gLayout->addWidget(passwordText, 2, 1);
    passwordText->setEchoMode(QLineEdit::Password);

    gLayout->addWidget(new QLabel("ID Card"), 3, 0);
    gLayout->addWidget(idNumText, 3, 1);

    gLayout->addWidget(new QLabel("Phone Number"), 4, 0);
    gLayout->addWidget(phoneNumText, 4, 1);

    mainLayout->addLayout(gLayout);

    auto okButton = new QPushButton(tr("Save"));
    auto cancelButton = new QPushButton(tr("Cancel"));
    cancelButton->setDefault(true);
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}
