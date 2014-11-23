#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <pvz.h>
#include <QTimer>

class Zombie : public PvZ
{
public:
    Zombie();
    QPointF getZombieLocation();
    void setZombieLocation(int column, int row);
    QTimer *eatTimer;
protected:
    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;
    QPointF zombieLocation;

};

#endif // ZOMBIE_H
