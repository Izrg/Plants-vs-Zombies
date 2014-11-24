#pragma once
#ifndef PVZ_H
#define PVZ_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <QList>

class myView;
class PvZ : public QGraphicsPixmapItem
{
public:
    PvZ();
    char gametype;
    QString name;

    myView *mV;

    QList<QGraphicsPixmapItem*>* instances;
};

#endif // PVZ_H
