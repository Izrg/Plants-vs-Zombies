#ifndef CHOMPER_H
#define CHOMPER_H

#include "attack.h"

class Chomper : public Attack
{
public:
    Chomper();
    void advance(int phase);
    enum{W=50}; // Plant size;
    static int rateCount,rateMax;
    // Plant interface
public:
    void onPlant(myView *rMV);
};

#endif // CHOMPER_H
