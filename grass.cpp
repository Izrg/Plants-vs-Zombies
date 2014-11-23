#include "grass.h"

Grass::Grass()
{
}


Grass::Grass(bool dark)
{
    QPixmap *pix;
    if(dark) pix = new QPixmap(":/grass1/darkGrass.PNG");
    else pix = new QPixmap(":/grass2/lightGrass.PNG");
    setPixmap(*pix);
    gametype = 'G';
    name = "Grass";
}
