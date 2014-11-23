#ifndef SUN_H
#define SUN_H
#include <pvz.h>
#include <QPixmap>
#include <QPoint>
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class Sun : public PvZ
{
public:
    Sun(int row, int column, bool falling);

    QPointF p;
    QPointF sunLocation;
    QPixmap sunPix;

    bool isFalling;
    enum {W= 35};
    void advance(int phase);
    void setLocation(int rX, int rY);
    void setLocation(QPointF rLoc);
    QPointF getLocation();
    int endRow;

};

#endif // SUN_H
