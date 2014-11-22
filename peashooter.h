#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include <attack.h>

class Peashooter : public Attack
{
public:
    Peashooter(myView *rMV = 0);
    myView *mV;


    // Plant interface
public:
    QString getImagePath();

    // Plant interface
public:
    void onPlant();
};

#endif // PEASHOOTER_H
