#include "ref.h"

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

    name = "Peashooter";
    setPixmap(QPixmap(":/Plants/PeaShooter.gif"));


    rateMax = (int)((double)rate * 10);
}

QString Peashooter::getImagePath()
{
    return ":/Plants/PeaShooter.gif";
}

void Peashooter::onPlant(myView *rMV)
{
    mV = rMV;
    rateCount = 0;
    instances->back()->setData(RATE_INDEX, this->rateCount);

}

void Peashooter::advance(int phase)
{
    if(!phase) return;

    //For each peashooter instance.
    for(int i = 0; i < instances->size(); i ++)
    {
        if(mV->zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->isEmpty())
        {
            //Reset the zombie shooting
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
        }

        //If the plant is shooting...
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            //CHANGE THE RATE AT WHICH BULLETS ARE SHOT
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
            {
                mV->plantShoot(instances->at(i)->data(PvZ::PLANT_TYPE).toInt(),i,false); // Call the plant shoot method to shoot a bullet.
            }
            continue;
        }
        for(int j=0; j < (mV->zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->size()); j++)
        {
            if(mV->zombieGridList->at(j) <= 0) continue;
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }

    }

    ++rateCount %= rateMax;
}
