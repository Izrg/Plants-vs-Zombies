#pragma once
#ifndef GRASS_H
#define GRASS_H

#include <QPixmap>

#include "pvz.h"

class Grass : public PvZ
{
public:
    Grass();
    QPixmap *getGrass(bool dark);
private:
    QPixmap* otherGrass;
};

#endif // GRASS_H
