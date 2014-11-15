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
    qDebug() << "End row: " << endRow << endl;
    qDebug() << "Column: " << column << endl;
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

    p = this->pos();
    setPos(p.x(), p.y() + 5);

}


