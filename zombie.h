#ifndef ZOMBIE_H
#define ZOMBIE_H
#pragma once

#include "pvz.h"

#include <QTimer>
#include <QList>

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

#endif // ZOMBIE_H
