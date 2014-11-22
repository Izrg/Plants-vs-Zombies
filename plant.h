#ifndef PLANT_H
#define PLANT_H
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <myview.h>
class Plant : public QGraphicsPixmapItem
{
public:
    Plant();
    void setImage(QPixmap rPix);
    virtual QString getImagePath();
    virtual void onPlant();
    myView *mV;
    QTimer *rateTimer;
    int getCost();
    double getRate();
    QPointF getPlantLocation();
    void setPlantLocation(int row, int column);

public slots:
    void rateFunc();

protected:
    int cost;
    int life;
    int range;
    int damage;
    double rate;
    double seeding;
    QPointF plantLocation;
private:
    enum {W= 50};
};

#endif // PLANT_H
