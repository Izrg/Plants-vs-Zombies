#include "ref.h"
Wallnut::Wallnut()
{
    this->cost = 50;
    this->life = 72;
    this->range = 0;
    this->rate = 0;
    this->damage = 0;
    this->bomb = false;
    this->seeding = 30;
    this->sun = false;
    this->need = false;

    name = "Wallnut";

    setPixmap(QPixmap(":/Plants/Wallnut_body.png").scaled(W,W));
}

void Wallnut::advance(int phase)
{
    if(!phase) return;
    //For each walnut planted
    for(int i = 0; i < instances->size(); i++){
        //Change the walnut picture if it is below a certain threshold.
        if(instances->at(i)->data(PvZ::INSTANCE_LIFE).toInt() <= 24)
        {
            instances->at(i)->setPixmap(QPixmap(":/Plants/Wallnut_cracked2.png").scaled(W,W));
        }else if(instances->at(i)->data(PvZ::INSTANCE_LIFE).toInt() <= 48){
            instances->at(i)->setPixmap(QPixmap(":/Plants/Wallnut_cracked1.png").scaled(W,W));
        }else{
            continue;
        }
    }
}

void Wallnut::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void Wallnut::onPlant(myView *rMV)
{
    mV = rMV;
}
