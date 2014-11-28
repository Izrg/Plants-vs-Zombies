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
class Bullet;
class Grass;
class Zombie;
class Regular;
class QGraphicsScene;
class Plant;
class myView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit myView(QWidget *parent = 0,mainGame *rMG = 0);

    //List for Plant Parent Classes
    QList <Plant*> *plantObj;


    //Lists for Zombies
    QList <Zombie*> *zombieObj; //Holds the "parent" class
    QList<QList<QGraphicsPixmapItem*>*> *zombieGridList; //Holds references to the children being drawn
    //Level Params ?


    int maxZombies; // Holds the max number of zombies for this level.
    int currentZombies; // Holds the number of zombies spawned so far.

    //Initilize Suns.
    Sun *sun;
    //Initilize bullets.
    Bullet *bullet;

    mainGame *mG; // mainGame forward declaration.
    QGraphicsScene *scene; // The graphics scene.

    enum {ROWS = 5, COLUMNS = 10};
    enum{COMMON_FACTOR = 10}; // Common factor used between classes.

    QRectF grid[ROWS][COLUMNS];
    QGraphicsPixmapItem *plantGrid [ROWS][COLUMNS];

    Grass *grass;

    QSignalMapper* mapper; //For mapping signals -> let's us pass values to slots
    QSignalMapper* zombieMapper; //For mapping signals -> let's us pass values to slots
    //Variables to control the height and width of each grid block.
    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);

    void zombieEat(int,int); // Called when the zombie eats plant brains.
    void plantShoot(int,int,bool);
    void damageZombie(int zombieObject,int zombieInstance,int damage, bool slow);
public slots:
    void sunSpawn(QObject*);
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
