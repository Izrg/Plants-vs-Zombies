#pragma once
#ifndef MYVIEW_H
#define MYVIEW_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRect>
#include <QSignalMapper>
#include <QPushButton>
#include <QMouseEvent>

#include "maingame.h"
#include "mainwindow.h"

class QMouseEvent;
class mainGame;
class Sun;
class Grass;
class Zombie;
class Regular;
class QGraphicsScene;
class myView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit myView(QWidget *parent = 0,mainGame *rMG = 0);

    //Lists for Zombies
    QList <Zombie*> *zombieObj; //Holds the "parent" class
    QList<QList<QGraphicsPixmapItem*>*> *zombieGridList; //Holds references to the children being drawn

    //Level Params ?
    int maxZombies; // Holds the max number of zombies for this level.
    int currentZombies; // Holds the number of zombies spawned so far.

    //Initilize Suns.
    Sun *sun;

    mainGame *mG; // mainGame forward declaration.
    QGraphicsScene *scene; // The graphics scene.

    enum {ROWS = 5, COLUMNS = 10};

    QRectF grid[ROWS][COLUMNS];
    bool gridFill[ROWS][COLUMNS];

    Grass *grass;

    QSignalMapper* mapper; //For mapping signals -> let's us pass values to slots
    QSignalMapper* zombieMapper; //For mapping signals -> let's us pass values to slots
    //Variables to control the height and width of each grid block.
    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);

public slots:
    void sunSpawn(QObject*);
    void zombieEat(QObject*);
    void zombieSpawner();
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QTimer *sunflowerTimer;
    QTimer *moveTimer;
    QTimer *sunTimer;
    QTimer *zombieSpawnTimer;

};

#endif // MYVIEW_H
