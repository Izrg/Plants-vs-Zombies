#include "sunflower.h"
#include "sun.h"
Sunflower::Sunflower(myView *rMV)
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
    mV = rMV;
    rateTimer = new QTimer(mV);

}

Sunflower::~Sunflower()
{
    rateTimer->stop();
}

QString Sunflower::getImagePath()
{
    return ":/Sunflower/Sunflower.gif";
}

void Sunflower::onPlant()
{
    mV->connect(rateTimer, SIGNAL(timeout()), mV->mapper, SLOT(map()));
    mV->mapper->setMapping(rateTimer,(QObject*)new QPointF(getPlantLocation()));
    rateTimer->start(this->getRate() * 3000);
}
