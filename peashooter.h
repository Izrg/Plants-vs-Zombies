#pragma once
#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "attack.h"

class myView;
class Peashooter : public Attack
{
public:
    Peashooter();
    static int rateCount,rateMax;
    // Plant interface
public:
    QString getImagePath();
    void advance(int phase);
    // Plant interface
public:
    void onPlant();
};

#endif // PEASHOOTER_H
