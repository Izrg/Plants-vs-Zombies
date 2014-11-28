#include "ref.h"

Cherrybomb::Cherrybomb()
{
    this->cost = 150;
    this->life = 9999;
    this->range = 1;
    this->rate = 1;
    this->damage = 90;
    this->bomb = true;
    this->seeding = 50;
    this->sun = false;
    this->need = false;

    name = "Cherrybomb";
    setPixmap(QPixmap(":/Plants/Cherrybomb.gif").scaled(W,W));


    rateMax = (int)((double)rate * 10);
}

void Cherrybomb::onPlant(myView *rMV)
{
    mV = rMV;
    rateCount = 0;
    instances->back()->setData(RATE_INDEX, this->rateCount);
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;

    for(int i =0; i < instances->size(); i ++)
    {
        int column = instances->at(i)->data(PvZ::COLUMN_INDEX).toInt();
        int row = instances->at(i)->data(PvZ::ROW_INDEX).toInt();
        if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
        {
            for(int j = (row == 0 ? row : row - 1); j <= (row == mV->ROWS - 1 ? row : row + 1); j++)
            {
                for(int k = 0; k < mV->zombieGridList->at(j)->size(); k++)
                {
                    if((mV->zombieGridList->at(j)->at(k)->pos().x() >= (column - 1) * mV->gameBlockWidth) && (mV->zombieGridList->at(j)->at(k)->pos().x() <= (column + 1) * mV->gameBlockWidth))
                    {
                        qDebug() << "Zombie Object: " << mV->zombieGridList->at(j)->at(k)->data(ZOMBIE_TYPE).toInt() << endl;
                        qDebug() << "Zombie instance: " << mV->zombieGridList->at(j)->at(k)->data(INSTANCE_INDEX).toInt() << endl;
                        mV->damageZombie(mV->zombieGridList->at(j)->at(k)->data(ZOMBIE_TYPE).toInt(),mV->zombieGridList->at(j)->at(k)->data(INSTANCE_INDEX).toInt(),damage,false);
                        //The plant grid space is now free.
                        mV->plantGrid[row][column] = NULL;
                        //Remove the plant as it blew up.
                        //delete mV->plantObj->at(instances->at(i)->data(PLANT_TYPE).toInt())->instances->at(instances->at(i)->data(INSTANCE_INDEX).toInt());
                        //mV->plantObj->at(instances->at(i)->data(PLANT_TYPE).toInt())->instances->removeAt(instances->at(i)->data(INSTANCE_INDEX).toInt());

                        //delete instances->at(i);
                        //instances->removeAt(i--);
                    }
                }
            }
            //Delete even if it doesnt kill anything.
            mV->plantGrid[row][column] = NULL;
            delete mV->plantObj->at(instances->at(i)->data(PLANT_TYPE).toInt())->instances->at(instances->at(i)->data(INSTANCE_INDEX).toInt());
            mV->plantObj->at(instances->at(i)->data(PLANT_TYPE).toInt())->instances->removeAt(instances->at(i)->data(INSTANCE_INDEX).toInt());

            //delete instances->at(i);
            instances->removeAt(i--);
        }
    }

    ++rateCount %= rateMax;
}
