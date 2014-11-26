#include "ref.h"

Plant::Plant()
{
    gametype = 'P';
    instanceLife = new QList<int>();
}

void Plant::onPlant(myView *rMV)
{


}

int Plant::getCost()
{
    return cost;
}

double Plant::getRate()
{
    return rate;
}

int Plant::getLife()
{
    return life;
}

void Plant::setLife(int newLife)
{
    life = newLife;
}

void Plant::advance(int phase)
{

}
