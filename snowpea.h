#ifndef SNOWPEA_H
#define SNOWPEA_H
#include "attack.h"

class Snowpea : public Attack
{
public:
    Snowpea();
    static int rateCount,rateMax;

    // QGraphicsItem interface
public:
    void advance(int phase);

    // Plant interface
public:
    void onPlant(myView *rMV);
};

#endif // SNOWPEA_H
