#pragma once
#ifndef SUN_H
#define SUN_H

#include "pvz.h"
#include <QList>

class Sun : public PvZ
{
public:
    Sun();

    enum {W= 35};
    void advance(int phase);
    void onCreate(bool falling, int endingRow);

    QList<bool> *isFalling;
    QList<int> *endRow;

};

#endif // SUN_H
