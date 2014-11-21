#ifndef SUN_H
#define SUN_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPoint>
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class Sun : public QGraphicsPixmapItem
{
public:
    Sun(int row, int column);

    QPointF p;
    QPointF sunLocation;
    QPixmap sunPix;
    enum {W= 35};
    void advance(int phase);
    void setLocation(int rX, int rY);
    QPointF getLocation();
    int endRow;

};

#endif // SUN_H
