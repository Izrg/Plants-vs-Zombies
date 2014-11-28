#pragma once
#ifndef PLANT_H
#define PLANT_H

#include <QTimer>
#include <QDebug>
#include <typeinfo>

#include "pvz.h"

class Plant : public PvZ
{
public:
    Plant();

    virtual void onPlant(myView *rMV) = 0;
    QTimer *rateTimer;

    int getCost();
    double getRate();
    int getLife();
    void setLife(int newLife);

    bool inRange;

    QList<int>* instanceLife;

public slots:
    void rateFunc();


    int cost;
    int life;
    int range;
    int damage;
    double rate;
    double seeding;
    bool slow;

    // QGraphicsItem interface
public:
    void advance(int phase);
};

#endif // PLANT_H
