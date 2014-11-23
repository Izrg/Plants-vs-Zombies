#ifndef ATTACK_H
#define ATTACK_H
#include <plant.h>
#include <myview.h>
#include <QRect>
class Attack : public Plant
{
public:
    Attack();

protected:
    bool slow;
    bool zombieInRange;
    QRectF* rangeRect;

    // Plant interface
public:
    QString getImagePath();

    // Plant interface
public:
    void onPlant();

public slots:
    void advance(int phase);
};

#endif // ATTACK_H
