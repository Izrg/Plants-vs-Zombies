#pragma once
#include "mainwindow.h"

#include <QApplication>
#include <QTime>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    //Seed the rand generator;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QApplication a(argc, argv);
    MainWindow w;
    //w.setAttribute(Qt::WA_DeleteOnClose);
    w.show();

    return a.exec();
}
