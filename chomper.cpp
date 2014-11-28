#include "ref.h"

Chomper::Chomper()
{
    this->cost = 150;
    this->life = 4;
    this->range = 1;
    this->damage = 150;
    this->rate = 5;
    this->seeding = 7.5;
    this->slow = false;

    name = "Chomper";
    setPixmap(QPixmap(":/Plants/Chomper.png").scaled(W,W));

    rateCount = 0;
    rateMax = (int)((double)rate * 10);

}

void Chomper::advance(int phase)
{
    if(!phase) return;

    for(int i = 0; i < instances->size(); i++){

        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable)){
            //CHANGE THE RATE AT WHICH BULLETS ARE SHOT
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount){
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                instances->at(i)->setPixmap(QPixmap(":/Plants/Chomper.png").scaled(W,W));
            }
            continue;
        }

        for(int j=0; j < (mV->zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->size()); j++)
        {
            if(instances->at(i)->collidesWithItem(mV->zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->at(j)))
            {

                instances->at(i)->setPixmap(QPixmap(":/Plants/Chomper_bite.gif").scaled(W,W));
                //Get the zombie object and instance
                int zombieObject = mV->zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::ZOMBIE_TYPE).toInt();
                int zombieInstance = mV->zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::INSTANCE_INDEX).toInt();
                //Damage the zombie.
                mV->damageZombie(zombieObject,zombieInstance,instances->at(i)->data(PvZ::INSTANCE_DAMAGE).toInt(),false);
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
            }
        }
    }
    ++rateCount %= rateMax;
}

void Chomper::onPlant(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, this->rateCount);
}
