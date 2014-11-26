#include "ref.h"

Grass::Grass()
{
    otherGrass = new QPixmap(":/grass2/lightGrass.PNG");
    setPixmap(QPixmap(":/grass1/darkGrass.PNG"));
    gametype = 'G';
    name = "Grass";
}

QPixmap* Grass::getGrass(bool dark)
{
    QPixmap tempPix = pixmap();
    if(dark) return &tempPix;
    return otherGrass;
}
