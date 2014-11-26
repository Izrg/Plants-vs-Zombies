#include "ref.h"

Sunflower::Sunflower()
{
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
    //mV = rMV;
    //rateTimer = new QTimer(mV);

    name = "Sunflower";
    setPixmap(QPixmap(":/Sunflower/Sunflower.gif"));
}

void Sunflower::advance(int phase)
{
    if(!phase) return;

}

Sunflower::~Sunflower()
{
    rateTimer->stop();
}

QString Sunflower::getImagePath()
{
    return ":/Sunflower/Sunflower.gif";
}

void Sunflower::onPlant(myView *rMV)
{
    mV = rMV;
}
