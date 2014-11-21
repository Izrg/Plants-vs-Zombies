#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include <attack.h>

class Peashooter : public Attack
{
public:
    Peashooter();



    // Plant interface
public:
    QString getImagePath();
};

#endif // PEASHOOTER_H
