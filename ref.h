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

    void onPlant();

    QTimer *rateTimer;

    int getCost();
    double getRate();
    int getLife();
    void setLife(int newLife);

    bool inRange;

    QList<int>* instanceLife;

public slots:
    void rateFunc();

protected:
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
    void onSpawn();

    QTimer *eatTimer;

    QList<int>* instanceLife;

protected:
    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;
};

class Attack : public Plant
{
public:
    Attack();
    void onPlant();

public slots:
    void advance(int phase);

protected:
    bool slow;
    bool zombieInRange;
    QRectF* rangeRect;
    QGraphicsItem *tempItem;
};

class Defence : public Plant
{
public:
    Defence();
    void onPlant();

protected:
    int splash;
    bool bomb;
    bool sun;
    bool need;
};

class Sunflower : public Defence
{
public:
    Sunflower(myView *rMV = 0);
    ~Sunflower();
    // Plant interface
public:
    QString getImagePath();


    // Plant interface
public:
    void onPlant();
};

class Peashooter : public Attack
{
public:
    Peashooter(myView *rMV = 0);
    void advance(int phase);

    // Plant interface
public:
    QString getImagePath();
    // Plant interface
public:
    void onPlant();
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
