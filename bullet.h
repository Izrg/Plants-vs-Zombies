#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "pvz.h"

class Bullet : public PvZ
{
public:
    Bullet();
    enum {W= 15};
    QPixmap *getBullet(bool slow);
private:
    QPixmap* snowBullet;
};

#endif // BULLET_H
