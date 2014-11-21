#include "plant.h"

Plant::Plant()
{

}

void Plant::setImage(QPixmap rPix)
{
    rPix = rPix.scaled(W,W);
    setPixmap(rPix);
}

QString Plant::getImagePath()
{

}

int Plant::getCost()
{
    return cost;
}
