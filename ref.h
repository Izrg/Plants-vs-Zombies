#pragma once
#ifndef REF_H
#define REF_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QList>
#include <QTimer>
#include <QDebug>
#include <typeinfo>
#include <QRect>

#include "myview.h"

class myView;
class PvZ : public QGraphicsPixmapItem
{
public:
    PvZ();
    char gametype;
    QString name;

    const static int CLASS_TYPE = 0;
    const static int INSTANCE_LIFE = 1;
    const static int RATE_INDEX = 2;
    const static int ROW_INDEX = 3;
    const static int COLUMN_INDEX = 4;
    const static int ZOMBIE_TYPE = 5;
    const static int PLANT_TYPE = 6;
    const static int INSTANCE_INDEX = 7;
    const static int INSTANCE_DAMAGE = 8;
    const static int INSTANCE_SLOW = 9;
    const static int Z_SPEED = 10;

    int rateCount,rateMax;
    myView *mV;

    QList<QGraphicsPixmapItem*>* instances;
    virtual void destroy(int index);


};
//GRASS
class Grass : public PvZ
{
public:
    Grass();
    QPixmap *getGrass(bool dark);
private:
    QPixmap* otherGrass;
};
//DIRT
class Dirt : public PvZ
{
public:
    Dirt();
    QPixmap *getDirt();
};

class Sun : public PvZ
{
public:
    Sun(int H);
    int gameBoardHeight;
    enum {W= 35, isFalling = 0, endRow = 1};
    void advance(int phase);
    void onCreate(bool falling, int endingRow);
    void destroy(int index);
};

class Plant : public PvZ
{
public:
    Plant();

    virtual void onPlant(myView *rMV);
    QList<QTimer*>* timers;
    QTimer *rateTimer;
    void advance(int phase);
    int getCost();
    double getRate();
    int getLife();
    void setLife(int newLife);
    bool inRange;
    virtual void destroy(int index);
    QList<int>* INSTANCE_LIFE;
    QList<int>* counter; // used to keep track of plant actions.

    int cost;
    int life;
    int range;
    int damage;
    double rate;
    double seeding;
    bool slow;

};

class Zombie : public PvZ
{
public:
    Zombie();

    int getAttack();
    QTimer *eatTimer;
    QList<int>* INSTANCE_LIFE;
    QList<int>* counter;

    int zombieLife;
    int equipmentLife;
    int attack;
    double rate;
    double speed;
    GraphicsItemFlag isEating;
    enum{COMMON_FACTOR = 10};
    virtual void onSpawn(myView *rMV) = 0;
    virtual void destroy(int index);
};

class Attack : public Plant
{
public:
    Attack();
    void onPlant(myView *rMV);

public slots:
    void advance(int phase);

    bool slow;
    bool zombieInRange;
    QRectF* rangeRect;
    QGraphicsItem *tempItem;
    virtual void destroy(int index);
};

class Bullet : public PvZ
{
public:
    Bullet(myView *rMV);
    enum {W= 15};
    int speed;
    QPixmap *getBullet(bool slow);
    void destroy(int index);
private:
    QPixmap* snowBullet;

public slots:
    void advance(int phase);


};

class Defence : public Plant
{
public:
    Defence();
    void onPlant(myView *rMV);
    void advance(int phase);
    virtual void destroy(int index);
    int splash;
    bool bomb;
    bool sun;
    bool need;
};

class Sunflower : public Defence
{
public:
    Sunflower();
    void advance(int phase);
    void destroy(int index);

    ~Sunflower();
    // Plant interface
public:
    QString getImagePath();


    // Plant interface
public:
    void onPlant(myView *rMV);
};
//*--------CherryBomb--------*
class Cherrybomb : public Defence
{
public:
    Cherrybomb();
    enum {W=50};
    void advance(int phase);
    void onPlant(myView *rMV);
    void destroy(int index);

};

//*--------SNOW PEA--------*
class Snowpea : public Attack
{
public:
    Snowpea();
    enum {W=50};
    void onPlant(myView *rMV);
    void destroy(int index);

    // QGraphicsItem interface
public:
    void advance(int phase);
};


//*--------Wallnut--------*
class Wallnut : public Defence
{
public:
    Wallnut();
    enum{W=50}; //size for the Wallnut pixmap
    void advance(int phase);
    void destroy(int index);

    // Plant interface
public:
    void onPlant(myView *rMV);
};

//*--------Chomper--------*
class Chomper : public Attack
{
public:
    Chomper();
    enum{W=50}; //size for the Wallnut pixmap
    void advance(int phase);
    void destroy(int index);
    // Plant interface
public:
    void onPlant(myView *rMV);
};

//*--------Peashooter--------*
class Peashooter : public Attack
{
public:
    Peashooter();
    void advance(int phase);
    void destroy(int index);

    // Plant interface
public:
    QString getImagePath();
    // Plant interface
public:
    void onPlant(myView *rMV);
};
//*-----------PotatoMine-------*
class PotatoMine : public Defence
{
public:
    PotatoMine();
    enum{W=50}; //size for the Potatomine pixmap
    void advance(int phase);
    void destroy(int index);
    void onPlant(myView *rMV);
};
//*---------Repeater------------*
class Repeater : public Attack
{
public:
    Repeater();
    enum{W=50}; //size for the Potatomine pixmap
    void advance(int phase);
    void destroy(int index);
    void onPlant(myView *rMV);
};

//*------------Regular-------*
class Regular : public Zombie
{
public:
    Regular();
    Regular(myView *mV);
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
    void onSpawn(myView *rMV);
    void destroy(int index);
};
//*----------FLAG-----------*
class Flag : public Zombie
{
public:
    Flag();
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
    void onSpawn(myView *rMV);
    void destroy(int index);
};
//*---------Conehead-------*
class Conehead : public Zombie
{
public:
    Conehead();
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
    void onSpawn(myView *rMV);
    void destroy(int index);
};
//*--------Buckethead----------*
class Buckethead : public Zombie
{
public:
    Buckethead();
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
    void onSpawn(myView *rMV);
    void destroy(int index);
};
//*-----------Newspaper------*
class Newspaper : public Zombie
{
public:
    Newspaper();
    enum{W=50}; //size for the zombie pixmap

    void advance(int phase); //advance function for the zombie.
    void onSpawn(myView *rMV);
    void destroy(int index);
};
#endif // REF_H
