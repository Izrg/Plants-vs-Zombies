#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;

Repeater::Repeater()
{
    //Set up the peashooter stats.
    this->cost = 200;
    this->life = 4;
    this->range = 9999;
    this->damage = 2;
    this->rate = 1.5;
    this->seeding = 7.5;
    this->slow = false;

    name = "Repeater";
    setPixmap(QPixmap(":/Plants/Repeater.png").scaled(W,W));

    rateMax = (int)((double)rate * 10);
    rateCount = 0;
}

void Repeater::advance(int phase)
{
    if(!phase) return;
    //For each peashooter instance.
    for(int i = 0; i < instances->size(); i ++)
    {
        if(zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->isEmpty())
        {
            //Reset the zombie shooting
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
        }else{
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }

        //If the plant is shooting...
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            //CHANGE THE RATE AT WHICH BULLETS ARE SHOT
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
            {
                mV->plantShoot(instances->at(i)->data(PvZ::PLANT_TYPE).toInt(),i,false); // Call the plant shoot method to shoot a bullet.
            }
        }

    }

    ++rateCount %= rateMax;
}

void Repeater::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void Repeater::onPlant(myView *rMV)
{
    mV = rMV;

    instances->back()->setData(RATE_INDEX, (this->rateCount - 1 + rateMax) % rateMax);
}
