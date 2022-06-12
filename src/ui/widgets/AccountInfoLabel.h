//
// Created by 黎明余光 on 2022/6/12.
//

#ifndef CPP_TERM_PROJECT_ACCOUNTINFOLABEL_H
#define CPP_TERM_PROJECT_ACCOUNTINFOLABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QTimer>
#include "db/Account.h"

class AccountInfoLabel : public QLabel {
Q_OBJECT

public:
    explicit AccountInfoLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~AccountInfoLabel();
    void setAccount(Account account);

signals:
    void doubleClicked(int accountId);

protected:
    Account account;
    QTimer timer;
    void mouseReleaseEvent(QMouseEvent *) override;

    void timerEvent(QTimerEvent *) override;

};


#endif //CPP_TERM_PROJECT_ACCOUNTINFOLABEL_H
