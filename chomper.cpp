#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;

Chomper::Chomper()
{
    this->cost = 150;
    this->life = 4;
    this->range = 1;
    this->damage = 150;
    this->rate = 42;
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

    for(int i = 0; i < instances->size(); i++)
    {

        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable)){
            //CHANGE THE RATE AT WHICH BULLETS ARE SHOT
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
            {
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                instances->at(i)->setPixmap(QPixmap(":/Plants/Chomper.png").scaled(W,W));
            }
            continue;
        }

        for(int j=0; j < (zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->size()); j++)
        {

            //CRASHES HERE WHEN CHOMPER EATS SECOND ZOMBIE IN SAME ROW AFTER IT ATE THE FIST ONE.
            //ONLY SOMETIMES IT SEEMS.
            //CRASHES WHEN CHOMPER EATS ZOMBIE AFTER ANOTHER CHOMPER ATE A ZOMBIE,
            if(instances->at(i)->collidesWithItem(zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->at(j)))
            {

                instances->at(i)->setPixmap(QPixmap(":/Plants/Chomper_bite.gif").scaled(W,W));
                //Get the zombie object and instance
                int zombieObject = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::ZOMBIE_TYPE).toInt();
                int zombieInstance = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::INSTANCE_INDEX).toInt();
                //Damage the zombie.
                mV->damageZombie(zombieObject,zombieInstance, j , instances->at(i)->data(PvZ::INSTANCE_DAMAGE).toInt(),false);
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
                instances->at(i)->setData(RATE_INDEX, this->rateCount);

            }
        }
    }
    ++rateCount %= rateMax;
}

void Chomper::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void Chomper::onPlant(myView *rMV)
{
    mV = rMV;

}
