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

    inRange = false;

    name = "Peashooter";
    setPixmap(QPixmap(":/Plants/PeaShooter.gif"));
}

QString Peashooter::getImagePath()
{
    return ":/Plants/PeaShooter.gif";
}

void Peashooter::onPlant(myView *rMV)
{
    mV = rMV;

}

void Peashooter::advance(int phase)
{
    if(!phase) return;

    //For each peashooter instance.
    for(int i = 0; i < instances->size(); i ++)
    {
        //If the plant is shooting...
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable)){
            //Increment the rateIndex; psudo timer counter.
            int tempInt = instances->at(i)->data(PvZ::rateIndex).toInt();
            tempInt ++;
            instances->at(i)->setData(PvZ::rateIndex,tempInt);
            //CHANGE THE RATE AT WHICH BULLETS ARE SHOT
            if(instances->at(i)->data(PvZ::rateIndex).toInt() % (int)(rate*10) == 1){
                mV->plantShoot(instances->at(i)->data(PvZ::plantType).toInt(),i,false); // Call the plant shoot method to shoot a bullet.
            }
            continue;
        }
        for(int j=0; j < (mV->zombieGridList->at(instances->at(i)->data((PvZ::rowIndex)).toInt())->size()); j++)
        {
            if(mV->zombieGridList->at(j) <= 0) continue;
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }

    }

    //for(int i = 0; i < mV->zombieGridList->at()//Peashooter Row)).size(); i++{

}
