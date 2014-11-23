#include "zombie.h"

Zombie::Zombie()
{
    gametype = 'Z';
}

QPointF Zombie::getZombieLocation()
{
    return zombieLocation;
}

void Zombie::setZombieLocation(int column, int row)
{
    zombieLocation.setX(column);
    zombieLocation.setY(row);
}
