//
// Created by 黎明余光 on 2022/6/11.
//

#ifndef CPP_TERM_PROJECT_DASHBOARDFINDER_H
#define CPP_TERM_PROJECT_DASHBOARDFINDER_H

#include <QtWidgets>

class DashBoardFinder : public QWidget {
    Q_OBJECT

public:
    DashBoardFinder(QWidget *parent = nullptr);

    QLineEdit* finder = new QLineEdit();
    QPushButton* finderButton = new QPushButton(tr("Find"));

public slots:
    void click();

signals:
    void find(int userId);
};


#endif //CPP_TERM_PROJECT_DASHBOARDFINDER_H
