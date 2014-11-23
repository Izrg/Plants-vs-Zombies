#include "peashooter.h"
#define quote(x) #x
Peashooter::Peashooter(myView *rMV)
{
    //Set up the peashooter stats.
    this->cost = 100;
    this->life = 4;
    this->range = 9999;
    this->damage = 1;
    this->rate = 1.5;
    this->seeding = 7.5;
    this->slow = false;
    mV = rMV;
    rateTimer = new QTimer(mV);
}

QString Peashooter::getImagePath()
{
    return ":/Plants/PeaShooter.gif";
}

void Peashooter::onPlant()
{

    rangeRect = new QRectF(this->getPlantLocation().x(),this->getPlantLocation().y(),this->range,mV->gameBlockHeight);
    qDebug() << "This range Rect: " << rangeRect << endl;
//    mV->connect(rateTimer, SIGNAL(timeout()), mV->mapper, SLOT(map()));
//    mV->mapper->setMapping(rateTimer,);
//    mV->connect(mapper,SIGNAL(mapped(Plant*)),mV,SLOT(checkZombie(Plant*)));
//    rateTimer->start(this->getRate() * 10000);
}

void Peashooter::advance(int phase)
{
    if(!phase) return;
    for (int i = 0; i < mV->scene->collidingItems(this).size(); i++)
        qDebug() << ((PvZ*)mV->scene->collidingItems(this).at(i))->gametype << " : " << i << endl;
//   for(mV->zombieIter = mV->zombies.begin(); mV->zombieIter != mV->zombies.end();){
//        if(rangeRect->contains((*(mV->zombieIter))->getZombieLocation())){
//            qDebug() << "IN RANGE!!" << endl;
//        }
//    }
}
