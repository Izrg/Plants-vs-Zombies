#pragma once
#ifndef REGULAR_H
#define REGULAR_H

#include "zombie.h"

class myView;
class Regular : public Zombie
{
public:
    Regular();

    enum{W=50}; //size for the zombie pixmap
    static int rateCount,rateMax;
    void advance(int phase); //advance function for the zombie.

    // Zombie interface
public:
    void onSpawn(myView *rMV);
};

#endif // REGULAR_H
