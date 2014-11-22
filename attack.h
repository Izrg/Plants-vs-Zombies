#ifndef ATTACK_H
#define ATTACK_H
#include <plant.h>
#include <myview.h>
class Attack : public Plant
{
public:
    Attack();

protected:
    bool slow;


    // Plant interface
public:
    QString getImagePath();

    // Plant interface
public:
    void onPlant();
};

#endif // ATTACK_H
