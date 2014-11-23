#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <pvz.h>
class Zombie : public PvZ
{
public:
    Zombie();
    QPointF getZombieLocation();
    void setZombieLocation(int column, int row);
protected:
    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;
    QPointF zombieLocation;

};

#endif // ZOMBIE_H
