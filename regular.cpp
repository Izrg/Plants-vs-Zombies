#include "ref.h"
#include <QDebug>

Regular::Regular()
{
    zombieLife = 10;
    equipmentLife = 0;
    attack = 1;
    rate = 0.5;
    speed = 5;

    //Load zombies image, and make it WxW
    setPixmap(QPixmap(":/Zombies/Regular.gif").scaled(W,W));

    rateCount = 0;
    rateMax = (int)((double)rate * 10);

}


void Regular::advance(int phase)
{
    if(!phase) return;

    for (int i = 0; i < instances->size(); i++)
    {   /*
        //The zombie moves if there is nothing at its position.
        int c = -1;
        for (int v = instances->at(i)->pos().y(); v > 0; c++) v -= mV->gameBlockWidth;
        if(mV->plantGrid[instances->at(i)->data(ROW_INDEX).toInt()][c] == NULL)
        {
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
        }*/

        for(int j = 0; j < mV->COLUMNS; j++)
        {
            //instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
            //If there is no plant in the current column, continue.
            if(mV->plantGrid[instances->at(i)->data(PvZ::ROW_INDEX).toInt()][j] == NULL) {
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,false);
                continue;
            }
            //If the zombie collides with a plant, set a flag and return.
            else if(instances->at(i)->collidesWithItem(mV->plantGrid[instances->at(i)->data(PvZ::ROW_INDEX).toInt()][j]))
            {
                //Set flag.
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
                break;
            }
        }

        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            //Check for rate of attack. TODO: SOME SERIOUS MATH!!
            if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount){
                mV->zombieEat(instances->at(i)->data(PvZ::ZOMBIE_TYPE).toInt(),i);
            }
            continue;
        }

        //Move the zombie
        instances->at(i)->setX(instances->at(i)->pos().x() - instances->at(i)->data(Z_SPEED).toDouble());

        //Remove if offscreen
        if(instances->at(i)->pos().x() + pixmap().width() <= 0)
        {
            delete instances->at(i);
            instances->removeAt(i--);
            //TODO
            //Probably add your END GAME thing here
            continue;
        }

        //Chekc if the zombie hits a plant
        //Go through each column of the current row.
    }
    ++rateCount %= rateMax;
}

void Regular::onSpawn(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, this->rateCount);
    instances->back()->setData(Z_SPEED,mV->gameBlockWidth / (this->speed * 10));
}

void Regular::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}
