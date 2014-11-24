#include "ref.h"

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

    name = "Sunflower";
    setPixmap(QPixmap(":/Sunflower/Sunflower.gif"));
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
    mV->mapper->setMapping(rateTimer,(QObject*)new QPointF(instances->back()->pos()));
    rateTimer->start(this->getRate() * 3000);
}
