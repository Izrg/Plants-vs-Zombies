#include "attack.h"
#include <QDebug>



Attack::Attack()
{

}

QString Attack::getImagePath()
{

}

void Attack::onPlant()
{

}

void Attack::advance(int phase)
{
    for(mV->zombieIter = mV->zombies.begin(); mV->zombieIter != mV->zombies.end();){
        if(rangeRect->contains((*(mV->zombieIter))->getZombieLocation())){
            qDebug() << "IN RANGE!!" << endl;
        }
    }
    qDebug() << "TEST ADVANCE PEASHOOTER" << endl;
}
