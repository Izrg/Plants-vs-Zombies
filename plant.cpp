#include "plant.h"

Plant::Plant()
{
    gametype = 'P';
}

void Plant::setImage(QPixmap rPix)
{
    rPix = rPix.scaled(W,W);
    setPixmap(rPix);
}

QString Plant::getImagePath()
{

}

void Plant::onPlant()
{

}

int Plant::getCost()
{
    return cost;
}

double Plant::getRate()
{
    return rate;
}

QPointF Plant::getPlantLocation()
{
    return plantLocation;
}

void Plant::setPlantLocation(int row, int column)
{
    plantLocation.setX(row);
    plantLocation.setY(column);
}

void Plant::rateFunc()
{

}
