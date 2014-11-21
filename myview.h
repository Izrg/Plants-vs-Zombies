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

class QMouseEvent;
class mainGame;
class Plant;

class myView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit myView(QWidget *parent = 0,mainGame *rMG = 0);

    //initilize the vector for the plants.
    vector <Plant*> plants;
    vector <Plant*>::iterator plantsIter;

    Ui::mainGame *ui;
    mainGame *mG; // mainGame forward declaration.
    Plant *pObj; //Plant forward declaration
    QLabel *plantLabel; // Store the plant gif
    QMovie *plantGif; // Holds the plant gif file.
    QGraphicsScene *scene; // The graphics scene.

    QPushButton *sunflowerBtn;

    enum {ROWS = 5, COLUMNS = 10};
    enum {W=50}; // The size used for the plant pixmaps
    int plantsIndex; // Index to keep track of how many plants are planted.

    QRectF grid[ROWS][COLUMNS];
    bool gridFill[ROWS][COLUMNS] = {{false}};

    QPixmap grass1; // Grass texture 1
    QPixmap grass2; // grass texture 2.
    QGraphicsPixmapItem *item; // Used to add items to the scene
    QMovie *plantItem; // Used to add plants to the scene.
    int sunIndex ; // Keep index of the suns.


    std::vector <Sun*> suns; // Vector to hold all the suns in.
    std::vector <Sun*>::iterator sunIter;

    int WIDTH, HEIGHT;
    int gameBlockHeight, gameBlockWidth;

    //Random number generator.
    int random(int x1, int x2);
    void acceptPlant(Plant *rPlant);
    void plantNewPlant();
signals:

public slots:

    void sunSpawn();
    void sunflowerSunSpawn();
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QTimer *sunflowerTimer;

};

#endif // MYVIEW_H
