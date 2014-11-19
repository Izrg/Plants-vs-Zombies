#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>
#include <maingame.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include <sun.h>
class QMouseEvent;
class myView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myView(QWidget *parent = 0);

    Ui::mainGame *ui;
    QGraphicsScene *scene;

    enum {ROWS = 5, COLUMNS = 10};
    QRectF grid[ROWS][COLUMNS];

    QLabel tempLbl;
    QPixmap grass1; // Grass texture 1
    QPixmap grass2; // grass texture 2.
    QPainter *qP;
    QGraphicsPixmapItem *item;

    int sunIndex = 0;

    std::vector <Sun*> suns;
    std::vector <Sun*>::iterator sunIter;

    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);

signals:

public slots:

    void sunSpawn();
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QTimer *moveTimer;
    QTimer *sunTimer;
};

#endif // MYVIEW_H
