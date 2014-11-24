#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include "plant.h"

#include <QRect>
class Attack : public Plant
{
public:
    Attack();
    void onPlant();

public slots:
    void advance(int phase);

protected:
    bool slow;
    bool zombieInRange;
    QRectF* rangeRect;
    QGraphicsItem *tempItem;
};

#endif // ATTACK_H
