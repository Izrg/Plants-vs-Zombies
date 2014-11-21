#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <maingame.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include <sun.h>
#include <QPushButton>
#include <plant.h>

class QMouseEvent;
class mainGame;
class myView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myView(QWidget *parent = 0,mainGame *rMG = 0);

    Ui::mainGame *ui;
    mainGame *mG; // mainGame forward declaration.


    QGraphicsScene *scene; // The graphics scene.

    QPushButton *sunflowerBtn;

    enum {ROWS = 5, COLUMNS = 10};

    QRectF grid[ROWS][COLUMNS];
    bool gridFill[ROWS][COLUMNS] = {{false}};

    QPixmap grass1; // Grass texture 1
    QPixmap grass2; // grass texture 2.
    QGraphicsPixmapItem *item; // Used to add items to the scene

    int sunIndex ; // Keep index of the suns.


    std::vector <Sun*> suns; // Vector to hold all the suns in.
    std::vector <Sun*>::iterator sunIter;

    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);
    void acceptPlant(Plant *rPlant);
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
