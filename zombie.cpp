#include "ref.h"
Zombie::Zombie()
{
    gametype = 'Z';
    instanceLife = new QList<int>();
    counter = new QList<int>();
}

void Zombie::onSpawn(myView *rMV)
{
    instanceLife->append(zombieLife + equipmentLife);
    counter->append(0);
    mV = rMV;
}

int Zombie::getAttack()
{
    return attack;
}
