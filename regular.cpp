#include "ref.h"
#include <QDebug>

Regular::Regular()
{

}

Regular::Regular(myView *rMV)
{
    zombieLife = 10;
    equipmentLife = 0;
    attack = 1;
    rate = 0.5;
    speed = 5;


    //Load zombies image, and make it WxW
    setPixmap(QPixmap(":/Zombies/Regular.gif").scaled(W,W));

    mV = rMV; // Sets the current mainview.

    eatTimer = new QTimer(mV);
}

void Regular::advance(int phase)
{
    if(!phase) return;

    for (int i = 0; i < instances->size(); i++)
    {
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
        instances->at(i)->setX(instances->at(i)->pos().x() - speed * 0.1);
    }

    /*
    //Need to not check all the items in the scene.
    for (int i = 0; i < mV->scene->collidingItems(this).size(); i++)
    {
        //If the zombie hits a plant, it starts to eat it.
        if(((PvZ*)mV->scene->collidingItems(this).at(i))->gametype == 'P'){
            if(eatTimer->isActive()){
                return;
            }

            mV->connect(eatTimer,SIGNAL(timeout()),mV->zombieMapper,SLOT(map()));
            mV->zombieMapper->setMapping(eatTimer,(QObject*) new QPointF(mV->scene->collidingItems(this).at(i)->pos()));
            mV->connect(mV->zombieMapper,SIGNAL(mapped(QObject*)),mV,SLOT(zombieEat(QObject*)));
            eatTimer->start(3000);
            return;

        }else{
            eatTimer->stop();
            //Move the sun down the scene.
            p = this->pos();
            //Change the location of the sun as it moves.
            setZombieLocation(p.x() - (this->speed * 0.1), p.y());
            //Set the new location on the screen
            setPos(p.x() - (this->speed * 0.1), p.y());

        }
    }*/
}
