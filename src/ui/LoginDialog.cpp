#include "LoginDialog.h"

#include <QtWidgets>

LoginDialog::LoginDialog(QWidget *parent)
        : QDialog(parent),
          nameText(new QLineEdit),
          passwordText(new QLineEdit) {
    auto nameLabel = new QLabel(tr("Username"));
    auto passwordLabel = new QLabel(tr("Password"));
    auto okButton = new QPushButton(tr("Login"));
    auto cancelButton = new QPushButton(tr("Exit"));

    auto gLayout = new QGridLayout;

//    gLayout->setColumnStretch(1, 2);
    gLayout->addWidget(nameLabel, 0, 0);
    gLayout->addWidget(nameText, 0, 1);

    gLayout->addWidget(passwordLabel, 1, 0);
    gLayout->addWidget(passwordText, 1, 1);
    passwordText->setEchoMode(QLineEdit::Password);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
//    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

    auto titleLabel = new QLabel("<h2>Azure Bank Inc.</h2>");
    auto usernameNoteLabel = new QLabel("Username can be either phone number or ID card.");

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(gLayout);
    mainLayout->addWidget(usernameNoteLabel);
    setLayout(mainLayout);

    connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
//    connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

    setWindowTitle(tr("Login"));
}

void LoginDialog::accept() {
//    QDialog::accept();
// TODO: real login
    if (nameText->text() == "true") {
        QDialog::accept();
        loggedIn(User{});
    } else {
        passwordText->clear();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Invalid username or password");
        msgBox.setInformativeText("The user is not found or the password is incorrect.");
        msgBox.exec();
    }
}