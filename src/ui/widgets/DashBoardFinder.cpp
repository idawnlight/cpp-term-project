//
// Created by 黎明余光 on 2022/6/11.
//

#include "DashBoardFinder.h"

#include <QRegularExpression>
#include <QRegularExpressionValidator>

DashBoardFinder::DashBoardFinder(QWidget *parent) : QWidget(parent) {
    auto headLayout = new QHBoxLayout();
    finder->setPlaceholderText("User ID...");
    finder->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*"), this));
    headLayout->addWidget(finder);
    headLayout->addWidget(finderButton);
    setLayout(headLayout);
    setMaximumWidth(360);

    connect(finderButton, &QAbstractButton::clicked, this, &DashBoardFinder::click);
}

void DashBoardFinder::click() {
    emit find(finder->text().toInt());
}

