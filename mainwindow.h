#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>

#include "maingame.h"
#include "fparcer.h"
#include <QListWidget>

namespace Ui {
class MainWindow;
}
class mainGame;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString levelFile;
    Fparcer* playerParce;
    int userLvl; // the users last level. Set to 1 if new user.
    ~MainWindow();
    mainGame *mG;
    QString lastUser;
    void restartGame();

private slots:
    void on_startBtn_clicked();

    void on_changeuserBtn_clicked();

    void on_userSelectorBox_activated(const QString &arg1);

    void on_addUserBtn_clicked();

    void on_deleteBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
