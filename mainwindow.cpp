#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <maingame.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBtn_clicked()
{
    //Hide this current window
    this->hide();

    //Show the new game window
    mG = new mainGame();
    mG->show();
}

