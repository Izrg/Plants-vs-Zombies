#include "peashooter.h"

Peashooter::Peashooter()
{
    //Set up the peashooter stats.
    this->cost = 100;
    this->life = 4;
    this->range = 9999;
    this->damage = 1;
    this->rate = 1.5;
    this->seeding = 7.5;
    this->slow = false;
}

QString Peashooter::getImagePath()
{
    return ":/Plants/PeaShooter.gif";
}
