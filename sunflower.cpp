#include "sunflower.h"

Sunflower::Sunflower()
{
    //sunMovie = new QMovie(":/Sunflower/Sunflower.gif");
    //Set up all the attributes of thhe plant.
    this->cost = 50;
    this->life = 4;
    this->range = 0;
    this->rate = 24;
    this->damage = 0;
    this->bomb = false;
    this->seeding = 7.5;
    this->sun = true;
    this->need = false;
}
