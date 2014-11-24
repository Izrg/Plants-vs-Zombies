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

#endif // PLANT_H
