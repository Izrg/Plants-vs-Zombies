#include "ref.h"
#include <QDebug>
Sun::Sun(myView *rmV)
{
    gametype = 'S';
    name = "Sun";

    mV = rmV;

    //Load sun image, and make it WxW
    setPixmap(QPixmap(":/sun/Sun.png").scaled(W,W));

    isFalling = new QList<bool>();
    endRow = new QList<int>();
}

void Sun::onCreate(bool falling, int endingRow)
{
    isFalling->append(falling);
    endRow->append(endingRow);
}

void Sun::advance(int phase)
{
    if(!phase) return;

    for(int i = 0; i < instances->size(); i++)
    {
        //Is the sun not falling?
        if(!isFalling->at(i)) continue;
        else if(instances->at(i)->pos().y() >= endRow->at(i) * mV->gameBlockHeight + mV->gameBlockHeight/4) isFalling->replace(i, false);
        else instances->at(i)->setY(instances->at(i)->pos().y() + 5);
    }
}

