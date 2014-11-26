#pragma once
#ifndef REF_H
#define REF_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <typeinfo>
#include <QRect>

#include "myview.h"

class myView;
class PvZ : public QGraphicsPixmapItem
{
public:
    PvZ();
    char gametype;
    QString name;

    const static int classType = 0;
    const static int instanceLife = 1;
    const static int rateIndex = 2;
    const static int rowIndex = 3;
    const static int columnIndex = 4;
    const static int zombieType = 5;
    const static int plantType = 6;
    const static int instanceIndex = 7;
    const static int damage = 8;


    myView *mV;

    QList<QGraphicsPixmapItem*>* instances;

};

class Grass : public PvZ
{
public:
    Grass();
    QPixmap *getGrass(bool dark);
private:
    QPixmap* otherGrass;
};

class Sun : public PvZ
{
public:
    Sun(myView *rmV);

    enum {W= 35};
    void advance(int phase);
    void onCreate(bool falling, int endingRow);

    QList<bool> *isFalling;
    QList<int> *endRow;

};

class Plant : public PvZ
{
public:
    Plant();

    virtual void onPlant(myView *rMV);
    QList<QTimer*>* timers;
    QTimer *rateTimer;
    void advance(int phase);
    int getCost();
    double getRate();
    int getLife();
    void setLife(int newLife);
    bool inRange;

    QList<int>* instanceLife;
    QList<int>* counter; // used to keep track of plant actions.

public slots:
    void rateFunc();

    int cost;
    int life;
    int range;
    int damage;
    double rate;
    double seeding;
};

class Zombie : public PvZ
{
public:
    Zombie();
    void onSpawn(myView *rMV);
    int getAttack();
    QTimer *eatTimer;
    QList<int>* instanceLife;
    QList<int>* counter;

    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;
    GraphicsItemFlag isEating;
    enum{COMMON_FACTOR = 10};
};

class Attack : public Plant
{
public:
    Attack();
    void onPlant(myView *rMV);

public slots:
    void advance(int phase);

    bool slow;
    bool zombieInRange;
    QRectF* rangeRect;
    QGraphicsItem *tempItem;
};

class Bullet : public PvZ
{
public:
    Bullet(myView *rMV);
    enum {W= 15};
    int speed;
public slots:
    void advance(int phase);


};

class Defence : public Plant
{
public:
    Defence();
    void onPlant(myView *rMV);
    void advance(int phase);

    int splash;
    bool bomb;
    bool sun;
    bool need;
};

class Sunflower : public Defence
{
public:
    Sunflower();
    void advance(int phase);
    ~Sunflower();
    // Plant interface
public:
    QString getImagePath();


    // Plant interface
public:
    void onPlant(myView *rMV);
};

class Peashooter : public Attack
{
public:
    Peashooter();
    void advance(int phase);

    // Plant interface
public:
    QString getImagePath();
    // Plant interface
public:
    void onPlant(myView *rMV);
};

class Regular : public Zombie
{
public:
    Regular();
    Regular(myView *mV);
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
};

#endif // REF_H
