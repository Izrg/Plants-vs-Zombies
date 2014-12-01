#include "ref.h"

Newspaper::Newspaper()
{
    zombieLife = 8;
    equipmentLife = 8;
    attack = 1;
    rate = 0.5;
    speed = 5;

    //Load zombies image, and make it WxW
    setPixmap(QPixmap(":/Zombies/Newspaper.gif").scaled(W,W));

    rateCount = 0;
    rateMax = (int)((double)rate * 10);
}

void Newspaper::advance(int phase)
{
    if(!phase) return;

    for (int i = 0; i < instances->size(); i++)
    {
        //If this zombies health is reduced to 8 (Equipment dies), lower its speed.

        if(instances->at(i)->data(PvZ::INSTANCE_LIFE).toInt() <= 8)
        {
            instances->at(i)->setData(Z_SPEED,QVariant(2));
        }

        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            //Check for rate of attack. TODO: SOME SERIOUS MATH!!
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount){
                mV->zombieEat(instances->at(i)->data(PvZ::ZOMBIE_TYPE).toInt(),i);
            }
            continue;
        }

        //Remove if offscreen
        if(instances->at(i)->pos().x() + pixmap().width() <= 0)
        {
            delete instances->at(i);
            instances->removeAt(i--);
            //TODO
            //Probably add your END GAME thing here
            continue;
        }

        //Move the zombie
        instances->at(i)->setX(instances->at(i)->pos().x() - instances->at(i)->data(Z_SPEED).toDouble());
        //Chekc if the zombie hits a plant

        //Go through each column of the current row.
        for(int j = 0; j < mV->COLUMNS; j++)
        {
            //If there is no plant in the current column, continue.
            if(mV->plantGrid[instances->at(i)->data(PvZ::ROW_INDEX).toInt()][j] == NULL) continue;
            //If the zombie collides with a plant, set a flag and return.
            if(instances->at(i)->collidesWithItem(mV->plantGrid[instances->at(i)->data(PvZ::ROW_INDEX).toInt()][j]))
            {
                //Set flag.
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
                return;
            }
        }

    }
    ++rateCount %= rateMax;
}

void Newspaper::onSpawn(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, this->rateCount);
    instances->back()->setData(Z_SPEED,mV->gameBlockWidth / (this->speed * 10));
}

void Newspaper::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}
