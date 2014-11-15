#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <maingame.h>
namespace Ui {
class MainWindow;
}
class mainGame;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    mainGame *mG;

private slots:
    void on_startBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
