#include "LoginDialog.h"
#include "db/Db.h"
#include "utility.h"

#include <QtWidgets>

LoginDialog::LoginDialog(QWidget *parent)
        : QDialog(parent),
          nameText(new QLineEdit),
          passwordText(new QLineEdit) {
    auto nameLabel = new QLabel(tr("Username"));
    auto passwordLabel = new QLabel(tr("Password"));
    auto okButton = new QPushButton(tr("Login"));
    okButton->setDefault(true);
//    auto cancelButton = new QPushButton(tr("Exit"));

    auto gLayout = new QGridLayout;

//    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(passwordLabel, 1, 0);
    gLayout->addWidget(passwordText, 1, 1);
    passwordText->setEchoMode(QLineEdit::Password);

    auto buttonLayout = new QHBoxLayout;
    auto debugUserButton = new QPushButton(tr("User"));
    auto debugEmployeeButton = new QPushButton(tr("Employee"));
    buttonLayout->addWidget(debugUserButton);
    buttonLayout->addWidget(debugEmployeeButton);
    connect(debugUserButton, &QAbstractButton::clicked, this, &LoginDialog::debugFillUser);
    connect(debugEmployeeButton, &QAbstractButton::clicked, this, &LoginDialog::debugFillEmployee);
    buttonLayout->addWidget(okButton);
//    buttonLayout->addWidget(cancelButton);

    auto usernameNoteLabel = new QLabel("<i>Username can be either phone number or ID card.</i>");
    gLayout->addWidget(usernameNoteLabel, 2, 0, 1, 2);
    gLayout->addLayout(buttonLayout, 3, 1, Qt::AlignRight);

    auto titleLabel = new QLabel("<h2>Azure Bank</h2>");

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(gLayout);
//    mainLayout->addWidget(usernameNoteLabel);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
//    connect(cancelButton, &QAbstractButton::doubleClicked, this, &QDialog::reject);

    setWindowTitle(tr("Login - Azure Bank"));

    // TODO: remove it
    if (Db::getStorage().count<User>() == 0) {
        User temp{"Light", "440102198001021230", "13700000000", Utility::password_hash("password")};
        Db::getStorage().insert(temp);
    }
    if (Db::getStorage().count<User>(where(c(&User::employeeId) > 0)) == 0) {
        User temp{"Light Admin", "440102198101021230", "13700000001", Utility::password_hash("password"), true};
        Db::getStorage().insert(temp);
    }
    if (Db::getStorage().count<Config>(where(c(&Config::key) == "interestRate")) == 0) {
        Config temp{"interestRate", "3.00"};
        Db::getStorage().insert(temp);
    }
}

void LoginDialog::accept() {
// TODO: real login
    try {
        auto users = Db::getStorage().get_all<User>(where(c(&User::phoneNumber) == nameText->text().toLocal8Bit().constData() or c(&User::idNumber) == nameText->text().toLocal8Bit().constData()));
        if (users.empty()) {
            throw std::invalid_argument("user not found");
        }
        auto user = users.front();
        if (Utility::password_verify(passwordText->text().toLocal8Bit().constData(), user.password.c_str())) {
            QDialog::accept();
            emit userLoggedIn(user);
        } else {
            throw std::invalid_argument("wrong password");
        }
    } catch (const std::exception& e) {
        passwordText->clear();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Invalid username or password");
        msgBox.setInformativeText("The user is not found or the password is incorrect.");
        msgBox.exec();
    }
}

void LoginDialog::debugFillUser() {
    nameText->setText("440102198001021230");
    passwordText->setText("password");
}

void LoginDialog::debugFillEmployee() {
    nameText->setText("440102198101021230");
    passwordText->setText("password");
}
