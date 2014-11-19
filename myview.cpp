#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>
myView::myView(QWidget *parent) :
    QGraphicsView(parent)
{
    grass1.load(":/grass1/darkGrass.PNG");
    grass2.load(":/grass2/lightGrass.PNG");
    //Set up the game board.
    WIDTH = parent->width() -10;
    HEIGHT = parent->height() - 5;
    scene = new QGraphicsScene(this);
    setScene(scene);

    //Set the size of hte screen.
    QRectF rect(0,0,WIDTH,HEIGHT);
    setSceneRect(rect);

    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;
    QPen myPen = QPen(Qt::red);

    //Set up intial step counters
    int widthStep = 0;
    int heightStep = 0;
    bool dark = true;

//    //This loop is used to draw the grid.
    for(int i = 0; i < ROWS; i ++){
        for (int j = 0; j < COLUMNS; j++){
            //Alternate between dark and light grass squares.
            if(dark){
                item = new QGraphicsPixmapItem(grass1);
                dark = false;
            }else {
                item = new QGraphicsPixmapItem(grass2);
                dark = true;
            }
            //Set the new grid square.
            QRectF tempRect (widthStep,heightStep, gameBlockWidth, gameBlockHeight);
            //Add the new rectangle to the array to hold the grid.
            grid[i][j] = tempRect;
            //Add the grass texture to the grid.
            item->setPos(widthStep,heightStep);
            scene->addItem(item);
            widthStep += gameBlockWidth;

        }
        dark = !(dark);
        //Move down a row based on the block height.
        heightStep += gameBlockHeight;
        //Reset the width step to start drawing at he left side of screen again.
        widthStep = 0;
    }

    //Add an initial sun and add it to the scene.
    suns.push_back(new Sun(((this->random(0,ROWS-1))*gameBlockHeight +(gameBlockHeight/4)),(this->random(0,COLUMNS-1)*gameBlockWidth + (gameBlockWidth/4))));
    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);

    moveTimer = new QTimer(this);
    sunTimer = new QTimer(this);
}

//Returns a random number.
int myView::random(int x1, int x2)
{
    return qrand() % ((x2 + 1) - x1) + x1;
}

void myView::sunSpawn()
{
    //Add a new sun.
    suns.push_back(new Sun(((this->random(0,ROWS-1))*gameBlockHeight +(gameBlockHeight/4)),(this->random(0,COLUMNS-1)*gameBlockWidth + (gameBlockWidth/4))));
    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);
}

void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;
    QPointF tempPoint = event->pos();
    //Iterate through all the current suns.
    for(sunIter = suns.begin(); sunIter != suns.end(); sunIter++){
        //If the user clicks within the range of the sun...
        if((qAbs(tempPoint.x() - (*(*sunIter)).getLocation().x()) <= range) && (qAbs(tempPoint.y() - (*(*sunIter)).getLocation().y()) <= range)){
            qDebug() << "Sun!" << endl;
        }
    }

}
