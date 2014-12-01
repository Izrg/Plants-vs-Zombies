#include "ref.h"
extern QList<QObject*> *flowerSuns = new QList<QObject*>();

Sunflower::Sunflower()
{
    //Set up all the attributes of thhe plant.
    this->cost = 50;
    this->life = 4;
    this->range = 0;
    this->rate = 5;
    this->damage = 0;
    this->bomb = false;
    this->seeding = 7.5;
    this->sun = true;
    this->need = false;

    name = "Sunflower";
    setPixmap(QPixmap(":/Sunflower/Sunflower.gif"));

    rateMax = (int)((double)rate * 10);
    rateCount = 0;
}

void Sunflower::advance(int phase)
{
    if(!phase) return; //For keeping time
    for(int i = 0; i < instances->size(); i++)
        if(instances->at(i)->data(RATE_INDEX).toInt() == rateCount)
            flowerSuns->append((QObject*)(new QPointF(instances->at(i)->pos().y(), instances->at(i)->pos().x())));
    if(++rateCount > rateMax) rateCount = 0;
}

void Sunflower::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

Sunflower::~Sunflower()
{
}

QString Sunflower::getImagePath()
{
    return ":/Sunflower/Sunflower.gif";
}

void Sunflower::onPlant(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, (this->rateCount - 1) % rateMax);


}
