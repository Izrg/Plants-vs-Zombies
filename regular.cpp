#include "regular.h"
#include <QDebug>

Regular::Regular(int row, int column, myView *rMV)
{
    this->zombieLife = 10;
    this->equipmentLife = 0;
    this->attack = 1;
    this->rate = 0.5;
    this->speed = 5;


    //Load zombies image, and make it WxW
    regularPix.load(":/Zombies/Regular.gif");
    regularPix = regularPix.scaled(W,W);

    mV = rMV; // Sets the current mainview.

    //Stores the zombies current location.
    setZombieLocation(column,row);

    //set the zombies position on the screen.
    setPos(column,row);
    setPixmap(regularPix);

    eatTimer = new QTimer(mV);
}

void Regular::advance(int phase)
{

    if(!phase) return;
    for (int i = 0; i < mV->scene->collidingItems(this).size(); i++)
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
            setZombieLocation(p.x() - 1, p.y());
            //Set the new location on the screen
            setPos(p.x() - 1, p.y());

        }
}
