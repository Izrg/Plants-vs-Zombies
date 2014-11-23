#ifndef PVZ_H
#define PVZ_H

#include <QGraphicsPixmapItem>

class PvZ : public QGraphicsPixmapItem
{
public:
    PvZ();
    char gametype;
    QString name;

};

#endif // PVZ_H
