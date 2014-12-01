#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;

Cherrybomb::Cherrybomb()
{
    this->cost = 150;
    this->life = 4;
    this->range = 1;
    this->rate = 2;
    this->damage = 90;
    this->bomb = true;
    this->seeding = 50;
    this->sun = false;
    this->need = false;

    name = "Cherrybomb";
    setPixmap(QPixmap(":/Plants/Cherrybomb.gif").scaled(W,W));
    rateCount = 0;


    rateMax = (int)((double)rate * 10);
}

void Cherrybomb::onPlant(myView *rMV)
{
    mV = rMV;
    instances->back()->setData(RATE_INDEX, (this->rateCount + rateMax - 1) % rateMax);
}

void Cherrybomb::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;

    for(int i =0; i < instances->size(); i ++)
    {
        int column = instances->at(i)->data(PvZ::COLUMN_INDEX).toInt();
        qDebug() << "Column: " << column << endl;
        int row = instances->at(i)->data(PvZ::ROW_INDEX).toInt();
        qDebug() << "Row: " << row << endl;
        qDebug() << "IRater index: " << instances->at(i)->data(RATE_INDEX).toInt() << endl;
        if(instances->at(i)->data(PvZ::RATE_INDEX).toInt() == this->rateCount)
        {
            for(int j = (row == 0 ? row : row - 1); j <= (row == mV->ROWS - 1 ? row : row + 1); j++)
            {
                int size = zombieGridList->at(j)->size();
                for(int k = 0; k < zombieGridList->at(j)->size(); k++)
                {
                    //CRASHES HERE RANDOMLY, NOT BED
                    //Crashed when zombie was 2 spaces right from cherrybomb.
                    qDebug() << "This happend" << endl;

                    if((zombieGridList->at(j)->at(k)->pos().x() >= (column - 1) * mV->gameBlockWidth - (mV->gameBlockWidth/4)) && (zombieGridList->at(j)->at(k)->pos().x() <= (column + 2) * mV->gameBlockWidth + (mV->gameBlockWidth/4)))
                    {
                        qDebug() << "Zombie Object: " << zombieGridList->at(j)->at(k)->data(ZOMBIE_TYPE).toInt() << endl;
                        qDebug() << "Zombie instance: " << zombieGridList->at(j)->at(k)->data(INSTANCE_INDEX).toInt() << endl;
                        mV->damageZombie(zombieGridList->at(j)->at(k)->data(ZOMBIE_TYPE).toInt(),zombieGridList->at(j)->at(k)->data(INSTANCE_INDEX).toInt(), k ,damage,false);
                        if(zombieGridList->at(j)->size() < size) k--;

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
