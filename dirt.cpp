#include "ref.h"

Dirt::Dirt()
{
    setPixmap(QPixmap(":/Dirt/Dirt.PNG"));
    gametype = 'D';
    name = "Dirt";
}

QPixmap *Dirt::getDirt()
{
    QPixmap tempPix = pixmap();
    return &tempPix;
}
