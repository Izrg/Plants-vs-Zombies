#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>
#include <maingame.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QTimer>
#include <sun.h>
#include <QPushButton>
#include <plant.h>
#include <zombie.h>
#include <regular.h>
#include <grass.h>
class QMouseEvent;
class mainGame;
class Plant;
class Grass;
class myView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myView(QWidget *parent = 0,mainGame *rMG = 0);

    //initilize the vector for the plants.
    vector <Plant*> plants;
    vector <Plant*>::iterator plantsIter;   
    int plantsIndex; // Index to keep track of how many plants are planted.
    //Initilize the vector for the suns.
    vector <Sun*> suns;
    vector <Sun*>::iterator sunIter;
    int sunIndex ; // Keep index of the suns.
    //Initilize the vector for teh zombies.
    vector<Zombie*> zombies;
    vector<Zombie*>::iterator zombieIter;
    int zombieIndex;
    int maxZombies; // Holds the max number of zombies for this level.
    int currentZombies; // Holds the number of zombies spawned so far.

    mainGame *mG; // mainGame forward declaration.
    Plant *pObj; //Plant forward declaration
    QLabel *plantLabel; // Store the plant gif
    QMovie *plantGif; // Holds the plant gif file.
    QGraphicsScene *scene; // The graphics scene.

    QPushButton *sunflowerBtn;

    enum {ROWS = 5, COLUMNS = 10};
    enum {W=50}; // The size used for the plant pixmaps

    QRectF grid[ROWS][COLUMNS];
    bool gridFill[ROWS][COLUMNS] = {{false}};


    Grass *g1,*g2;

    QGraphicsPixmapItem *item; // Used to add items to the scene
    QMovie *plantItem; // Used to add plants to the scene.

    QSignalMapper* mapper; //For mapping signals -> let's us pass values to slots

    //Variables to control the height and width of each grid block.
    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);
    void plantNewPlant();

public slots:
    void checkZombie(Plant*);
    void sunSpawn(QObject*);
    void zombieSpawner();
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QTimer *sunflowerTimer;
    QTimer *moveTimer;
    QTimer *sunTimer;
    QTimer *zombieSpawnTimer;

};

#endif // MYVIEW_H
