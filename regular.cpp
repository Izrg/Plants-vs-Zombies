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

    //mV = rMV; // Sets the current mainview.

    //eatTimer = new QTimer(mV);
}


void Regular::advance(int phase)
{
    if(!phase) return;

    for (int i = 0; i < instances->size(); i++)
    {
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            int tempInt = instances->at(i)->data(PvZ::rateIndex).toInt();
            tempInt ++;
            instances->at(i)->setData(PvZ::rateIndex,QVariant(tempInt));
            //Check for rate of attack. TODO: SOME SERIOUS MATH!!
            if(instances->at(i)->data(PvZ::rateIndex).toInt() % (int)(rate*50) == 1){
                mV->zombieEat(instances->at(i)->data(PvZ::zombieType).toInt(),i);
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
        instances->at(i)->setX(instances->at(i)->pos().x() - speed * 0.5);
        //Chekc if the zombie hits a plant
        //For each plant object....

        //Go through each column of the current row.
        for(int j = 0; j < mV->COLUMNS; j++)
        {
            //If there is no plant in the current column, continue.
            if(mV->plantGrid[instances->at(i)->data(PvZ::rowIndex).toInt()][j] == NULL) continue;
            //If the zombie collides with a plant, set a flag and return.
            if(instances->at(i)->collidesWithItem(mV->plantGrid[instances->at(i)->data(PvZ::rowIndex).toInt()][j]))
            {
                //Set flag.
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
                return;
            }
        }

    }
}
