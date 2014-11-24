#pragma once
#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "attack.h"

class myView;
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

#endif // PEASHOOTER_H
