#pragma once
#ifndef DEFENCE_H
#define DEFENCE_H

#include "plant.h"

class Defence : public Plant
{
public:
    Defence();
    void onPlant(myView *rMV);

    int splash;
    bool bomb;
    bool sun;
    bool need;

    // QGraphicsItem interface
public:
    void advance(int phase);
};

#endif // DEFENCE_H
