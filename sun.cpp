#include "sun.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
Sun::Sun(int row, int column, bool falling)
{
    //Is the sun falling or not?
    isFalling = falling;
    //Load sun image, and make it WxW
    sunPix.load(":/sun/Sun.png");
    sunPix = sunPix.scaled(W,W);
    //Set the resting point.
    endRow = row;

    //Stores the suns current location.
    setLocation(column,row);
    if(!isFalling){
        setPos(sunLocation.x(),sunLocation.y()); // Set the sun position based on the sunflower
    }else{
        setPos(column,this->pos().y());
    }

    //set the sun position on the screen.
    setPixmap(sunPix);
}

void Sun::advance(int phase)
{

    //If it is not falling, dont do anything.
    if(!isFalling){
        return;
    }

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
//Sets the suns location based on QPOintF
void Sun::setLocation(QPointF rLoc)
{
    sunLocation = rLoc;
}

//Return the suns current location
QPointF Sun::getLocation()
{
    return sunLocation;
}


