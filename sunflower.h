#pragma once
#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "defence.h"

class myView;
class Sunflower : public Defence
{
public:
    Sunflower(myView *rMV = 0);
    ~Sunflower();
    // Plant interface
public:
    QString getImagePath();


    // Plant interface
public:
    void onPlant();
};

#endif // SUNFLOWER_H
