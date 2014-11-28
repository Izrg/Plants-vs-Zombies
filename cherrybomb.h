#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "defence.h"

class Cherrybomb : public Defence
{
public:
    Cherrybomb();

    // QGraphicsItem interface
public:
    void advance(int phase);
    static int rateCount,rateMax;
    // Plant interface
public:
    void onPlant(myView *rMV);
};

#endif // CHERRYBOMB_H
