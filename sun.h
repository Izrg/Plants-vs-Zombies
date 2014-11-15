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
    QPixmap sunPix;
    enum {W= 35};
    void advance(int phase);
    int endRow;


};

#endif // SUN_H
