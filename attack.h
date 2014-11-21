#ifndef ATTACK_H
#define ATTACK_H
#include <plant.h>
class Attack : public Plant
{
public:
    Attack();

protected:
    bool slow;


    // Plant interface
public:
    QString getImagePath();
};

#endif // ATTACK_H
