#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;

PotatoMine::PotatoMine()
{
    this->cost = 25;
    this->life = 4;
    this->range = 1;
    this->rate = 3;
    this->damage = 90;
    this->bomb = true;
    this->seeding = 30;
    this->sun = false;
    this->need = false;

    name = "Potatomine";
    rateCount = 0;
    rateMax = (int)((double)rate * 10);
    setPixmap(QPixmap(":/Plants/PotatoReady.gif").scaled(W,W));
}

void PotatoMine::advance(int phase)
{
    if(!phase) return;

    qDebug() << "Potates.size() Init: " << instances->size() << endl;
    for(int i = 0; i < instances->size(); i++)
    {
        //Set up Potato ready state (blows up zombies, yo)
        if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
        {
            //Set the plant flag and picture. its ready to blow.
            instances->at(i)->setPixmap(QPixmap(":/Plants/PotatoReady.gif").scaled(W,W));
            instances->at(i)->setFlag(QGraphicsItem::ItemIsMovable,true);
        }

        qDebug() << "Potates.size() Loop Start: " << instances->size() << endl;
        qDebug() << "Potates Index : " << i << endl;
        //If the potatomine is ready to kill zombies...
        if(instances->at(i)->flags().testFlag(QGraphicsItem::ItemIsMovable))
        {
            for(int j=0; j < (zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->size()); j++)
            {

                //CRASHES HERE WHEN CHOMPER EATS SECOND ZOMBIE IN SAME ROW AFTER IT ATE THE FIST ONE.
                //ONLY SOMETIMES IT SEEMS.
                //CRASHES WHEN CHOMPER EATS ZOMBIE AFTER ANOTHER CHOMPER ATE A ZOMBIE,
                if(instances->at(i)->collidesWithItem(zombieGridList->at(instances->at(i)->data((PvZ::ROW_INDEX)).toInt())->at(j)))
                {

                    //Get the zombie object and instance
                    int zombieObject = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::ZOMBIE_TYPE).toInt();
                    int zombieInstance = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::INSTANCE_INDEX).toInt();
                    //Damage the zombie.
                    mV->damageZombie(zombieObject,zombieInstance, j , instances->at(i)->data(PvZ::INSTANCE_DAMAGE).toInt(),false);
                    qDebug() << "Potates.size() Before: " << instances->size() << endl;
                    //Remove the plant from the plant Grid.
                    mV->plantGrid[instances->at(i)->data(ROW_INDEX).toInt()][instances->at(i)->data(COLUMN_INDEX).toInt()] = NULL;
                    delete instances->at(i);
                    instances->removeAt(i);
                    i--;
                    qDebug() << "Potates.size() After: " << instances->size() << endl;

                    break;
                }
            }
        }
    }
    ++rateCount %= rateMax;
}

void PotatoMine::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void PotatoMine::onPlant(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, (this->rateCount - 1 + rateMax) % rateMax);
    instances->back()->setPixmap(QPixmap(":/Plants/PotatoPlant.png").scaled(15,15));
    instances->back()->setPos(instances->back()->pos().x() + (mV->gameBlockWidth/4),instances->back()->pos().y() + (mV->gameBlockHeight/4));
}
