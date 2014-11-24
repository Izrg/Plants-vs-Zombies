#include "ref.h"
Zombie::Zombie()
{
    gametype = 'Z';
    instanceLife = new QList<int>();
}

void Zombie::onSpawn()
{
    instanceLife->append(zombieLife + equipmentLife);
}
