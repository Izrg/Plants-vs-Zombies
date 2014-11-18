#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <mainwindow.h>
#include <QWidget>


namespace Ui {
class mainGame;
}
class MainWindow;
class myView;
class mainGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainGame(QWidget *parent = 0);

    Ui::mainGame *ui;
    int sunPoints;

    myView *mV;
    int getBlockHeight();
    ~mainGame();
    MainWindow *mW;

private slots:
    void on_sunflowerBtn_clicked();


private:

    QTimer *moveTimer;
    QTimer *sunTimer;

};

#endif // MAINGAME_H
