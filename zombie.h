#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <QGraphicsPixmapItem>

class Zombie : public QGraphicsPixmapItem
{
public:
    Zombie();
protected:
    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;

};

#endif // ZOMBIE_H
