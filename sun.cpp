#include "sun.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
Sun::Sun(int row, int column)
{
    //Load sun image, and make it WxW
    sunPix.load(":/sun/Sun.png");
    sunPix = sunPix.scaled(W,W);
    //Set the resting point.
    endRow = row;

    setLocation(column,row);

    //set the sun position on the screen.
    setPos(column,this->pos().y());
    setPixmap(sunPix);
}

void Sun::advance(int phase)
{
    if(!phase) return;
    //Checks if it is at the resting point.
    if(p.y() >= endRow){
        setPos(p.x(), p.y());
        return;
    }

    //Move the sun down the scene.
    p = this->pos();
    //Change the location of the sun as it moves.
    setLocation(p.x(), p.y() + 5);
    //Set the new location on the screen
    setPos(p.x(), p.y() + 5);

}

//Set teh suns current location
void Sun::setLocation(int rX, int rY)
{
    sunLocation.setX(rX);
    sunLocation.setY(rY);
}

//Return the suns current location
QPointF Sun::getLocation()
{
    return sunLocation;
}


