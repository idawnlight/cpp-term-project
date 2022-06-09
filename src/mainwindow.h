#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "db/Db.h"

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

public slots:
    void setUser(User user);

private:
    void createMenus();

    Db database;
    User user;
};

#endif // MAINWINDOW_H
