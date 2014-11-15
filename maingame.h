#ifndef MAINGAME_H
#define MAINGAME_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <mainwindow.h>



namespace Ui {
class mainGame;
}
class MainWindow;
class mainGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainGame(QWidget *parent = 0);

    enum {ROWS = 5, COLUMNS = 10};
    QRectF grid[ROWS][COLUMNS];

    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;
    QLabel tempLbl;
    QPixmap grass1;
    QPixmap grass2;
    QPainter *qP;

    //Random number generator.
    int random(int x1, int x2);


    int getBlockHeight();
    ~mainGame();
    MainWindow *mW;

private slots:
    void on_sunflowerBtn_clicked();

private:
    Ui::mainGame *ui;
    QGraphicsScene *scene;
    QTimer *moveTimer;
};

#endif // MAINGAME_H
