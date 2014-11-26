#pragma once
#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "defence.h"

class myView;
class Sunflower : public Defence
{
public:
    Sunflower();
    ~Sunflower();
    // Plant interface
public:
    QString getImagePath();
    void advance(int phase);

    // Plant interface
public:
    void onPlant();
};

#endif // SUNFLOWER_H
