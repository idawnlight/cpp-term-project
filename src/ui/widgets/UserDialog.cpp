#include "UserDialog.h"

UserDialog::UserDialog(QWidget *parent, User tUser, bool isEditable)
    : QDialog(parent),
      user(tUser),
      isEditable(isEditable) {
    setWindowTitle(tr("Edit User - Azure Bank"));

    auto mainLayout = new QVBoxLayout;

    auto gLayout = new QGridLayout;
    gLayout->setColumnMinimumWidth(1, 270);

    if (!isEditable) {
        nameText->setReadOnly(true);
        idNumText->setReadOnly(true);
        phoneNumText->setReadOnly(true);
    }

    gLayout->addWidget(new QLabel("User ID"), 0, 0);
    gLayout->addWidget(new QLabel(QString::number(user.id)), 0, 1);

    gLayout->addWidget(new QLabel("Name"), 1, 0);
    nameText->setText(QString(user.name.c_str()));
    gLayout->addWidget(nameText, 1, 1);

    gLayout->addWidget(new QLabel("Password"), 2, 0);
    passwordText->setPlaceholderText("Leave blank to keep original password.");
    gLayout->addWidget(passwordText, 2, 1);
    passwordText->setEchoMode(QLineEdit::Password);

    gLayout->addWidget(new QLabel("ID Card"), 3, 0);
    idNumText->setText(QString(user.idNumber.c_str()));
    gLayout->addWidget(idNumText, 3, 1);

    gLayout->addWidget(new QLabel("Phone Number"), 4, 0);
    phoneNumText->setText(QString(user.phoneNumber.c_str()));
    gLayout->addWidget(phoneNumText, 4, 1);

    if (user.employeeId != -1) {
        gLayout->addWidget(new QLabel("Employee ID"), 5, 0);
        gLayout->addWidget(new QLabel(QString::number(user.employeeId)), 5, 1);
    }

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
