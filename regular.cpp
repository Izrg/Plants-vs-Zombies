#include "regular.h"

Regular::Regular(int row, int column)
{
    this->zombieLife = 10;
    this->equipmentLife = 0;
    this->attack = 1;
    this->rate = 0.5;
    this->speed = 5;


    //Load zombies image, and make it WxW
    regularPix.load(":/Zombies/Regular.gif");
    regularPix = regularPix.scaled(W,W);


    //Stores the zombies current location.
    setLocation(column,row);

    //set the zombies position on the screen.
    setPos(column,row);
    setPixmap(regularPix);
}

void Regular::setLocation(int column, int row)
{
    regularLocation.setX(column);
    regularLocation.setY(row);
}
void Regular::advance(int phase)
{

    if(!phase) return;

    //Move the sun down the scene.
    p = this->pos();
    //Change the location of the sun as it moves.
    setLocation(p.x() - 1, p.y());
    //Set the new location on the screen
    setPos(p.x() - 1, p.y());

}
