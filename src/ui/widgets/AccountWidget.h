//
// Created by 黎明余光 on 2022/6/12.
//

#ifndef CPP_TERM_PROJECT_ACCOUNTWIDGET_H
#define CPP_TERM_PROJECT_ACCOUNTWIDGET_H

#include "db/Account.h"
#include "db/User.h"

#include <QtWidgets>

class AccountWidget : public QGridLayout {
    Q_OBJECT
public:
    AccountWidget(QWidget *parent = nullptr, int userId = -1);
    AccountWidget(QWidget *parent = nullptr, User user = {});

public slots:
    void fetchByUserId(int userId);

private:
    User user;
    Account current;
    Account savings;
    QLabel* topLabel = new QLabel();
    QVBoxLayout* currentLayout = new QVBoxLayout;
    QVBoxLayout* savingLayout = new QVBoxLayout;
    QLabel* currentLabel = new QLabel("<h2>Current</h2>");
    QLabel* currentContent = new QLabel();
    QLabel* savingLabel = new QLabel("<h2>Saving</h2>");
    QLabel* savingContent = new QLabel();
    QPushButton* openCurrentButton = new QPushButton(tr("Open Current Account"));
    QPushButton* openSavingButton = new QPushButton(tr("Open Saving Account"));
    QPushButton* closeCurrentButton = new QPushButton(tr("Close Current Account"));
    QPushButton* closeSavingButton = new QPushButton(tr("Close Saving Account"));

    void initWidget(bool showNotFound = true);
    void refreshWidget();
};

#endif //CPP_TERM_PROJECT_ACCOUNTWIDGET_H
