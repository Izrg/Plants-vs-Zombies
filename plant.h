#ifndef PLANT_H
#define PLANT_H
#include <QGraphicsPixmapItem>

class Plant : public QGraphicsPixmapItem
{
public:
    Plant();
    void setImage(QPixmap rPix);
    virtual QString getImagePath();
    int getCost();
protected:
    int cost;
    int life;
    int range;
    int damage;
    double rate;
    double seeding;
private:
    enum {W= 50};
};

#endif // PLANT_H
