#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;
QPixmap *Lawnmower::getLawnmower()
{
    QPixmap tempPix = pixmap();
    return &tempPix;
}

Lawnmower::Lawnmower()
{
    setPixmap(QPixmap(":/Lawnmower/Lawnmower.png").scaled(W,W));
    damage = 999;

    name = "Lawnmower";
    gametype  = 'L';
}

void Lawnmower::destroy(int index)
{

}

void Lawnmower::onPlant(myView *rMV)
{
    mV = rMV;
}

void Lawnmower::advance(int phase)
{
    if(!phase) return;

    for(int i =0; i < instances->size(); i++)
    {
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
           instances->at(i)->setX(instances->at(i)->pos().x() + 10);
           //Destroy the lawnmower when it goes off screen.
           if(instances->at(i)->pos().x() + pixmap().width() >= mV->WIDTH)
           {
               mV->scene->removeItem(instances->at(i));
               delete instances->at(i);
               instances->removeAt(i--);
               continue;
           }
        }

        for(int j=0; j < (zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->size()); j++)
        {
            if(instances->at(i)->collidesWithItem(zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->at(j)))
            {
                mV->plantGrid[instances->at(i)->data(ROW_INDEX).toInt()][instances->at(i)->data(COLUMN_INDEX).toInt()] = NULL;
                //Get the zombie object and instance
                int zombieObjectIndex = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::ZOMBIE_TYPE).toInt();
                int zombieInstanceIndex = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::INSTANCE_INDEX).toInt();
                qDebug() << "Zombie object: " << zombieObjectIndex << endl;
                qDebug() << "Zombie Instance: " << zombieInstanceIndex << endl;

                //delete mV->zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex);
                //mV->zombieObj->at(zombieObjectIndex)->instances->removeAt(zombieInstanceIndex);
                //Update preference.
                //for(int j = 0; j < mV->zombieObj->at(zombieObjectIndex)->instances->size(); j++) mV->zombieObj->at(zombieObjectIndex)->instances->at(j)->setData(PvZ::INSTANCE_INDEX, j);
                instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
                //Damage the zombie.
                mV->damageZombie(zombieObjectIndex,zombieInstanceIndex, j , damage ,false);

            }
        }
    }

}

