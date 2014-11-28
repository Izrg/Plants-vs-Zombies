#ifndef WALLNUT_H
#define WALLNUT_H
#include "defence.h"

class Wallnut : public Defence
{
public:
    Wallnut();
    enum{W=50}; //size for the Wallnut pixmap
    void advance(int phase);
    // Plant interface
public:
    void onPlant(myView *rMV);
};

#endif // WALLNUT_H
