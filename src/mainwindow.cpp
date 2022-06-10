#include "mainwindow.h"

#include <QMenuBar>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    setWindowTitle("Banking");

    createMenus();

//    User newUser{};
}

MainWindow::~MainWindow() {
}

void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *openAct = new QAction(tr("&Open..."), this);
    fileMenu->addAction(openAct);
//    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    QAction *saveAct = new QAction("Save As...", this);
//    fileMenu->addAction(saveAct);
//    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

//    fileMenu->addSeparator();

    QAction *exitAct = new QAction("Test", this);
    fileMenu->addAction(exitAct);
//    connect(exitAct, &QAction::triggered, this, &QWidget::close);

//    QMenu *toolMenu = menuBar()->addMenu(tr("&Tools"));
//
//    QAction *addAct = new QAction(tr("&Add Entry..."), this);
//    toolMenu->addAction(addAct);
//    connect(addAct, &QAction::triggered,
//            addressWidget, &AddressWidget::showAddEntryDialog);

//    editAct = new QAction(tr("&Edit Entry..."), this);
//    editAct->setEnabled(false);
//    toolMenu->addAction(editAct);
//    connect(editAct, &QAction::triggered, addressWidget, &AddressWidget::editEntry);

//    toolMenu->addSeparator();
//
//    removeAct = new QAction(tr("&Remove Entry"), this);
//    removeAct->setEnabled(false);
//    toolMenu->addAction(removeAct);
//    connect(removeAct, &QAction::triggered, addressWidget, &AddressWidget::removeEntry);

//    connect(addressWidget, &AddressWidget::selectionChanged,
//            this, &MainWindow::updateActions);
}

void MainWindow::setUser(User user) {
    QMessageBox::warning(this, tr("My Application"), "Employee");
    show();
}
