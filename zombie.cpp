#include "ref.h"
Zombie::Zombie()
{
    gametype = 'Z';
    counter = new QList<int>();
}

void Zombie::onSpawn(myView *rMV)
{
    counter->append(0);
    mV = rMV;
}

int Zombie::getAttack()
{
    return attack;
}
