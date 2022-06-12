//
// Created by 黎明余光 on 2022/6/12.
//

#include "AccountInfoLabel.h"

AccountInfoLabel::AccountInfoLabel(QWidget *parent, Qt::WindowFlags f)
        : QLabel(parent) {

}

AccountInfoLabel::~AccountInfoLabel() = default;

void AccountInfoLabel::setAccount(Account taccount) {
    account = taccount;
    setText(account.toString());
}

void AccountInfoLabel::timerEvent(QTimerEvent *) {
    timer.stop();
//    qDebug() << "single click";
}

void AccountInfoLabel::mouseReleaseEvent(QMouseEvent *) {
    if (timer.isActive()) {
        timer.stop();
        emit doubleClicked(account.id);
//        qDebug() << "double click";
    } else {
        timer.start(300);
    }
}
