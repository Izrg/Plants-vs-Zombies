#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>
#include <QMovie>
myView::myView(QWidget *parent, mainGame *rMG) :
    QGraphicsView(parent)
{

    //Set the sun index
    sunIndex = 0;
    //Load the grass images.
    grass1.load(":/grass1/darkGrass.PNG");
    grass2.load(":/grass2/lightGrass.PNG");
    //Set up the game board.
    WIDTH = parent->width();
    HEIGHT = parent->height();
    //Set up the scene
    scene = new QGraphicsScene(this);
    setScene(scene);

    //Set the main game object to the maingame
    mG = rMG;

    //Set the size of hte screen.
    QRectF rect(0,0,WIDTH,HEIGHT);
    setSceneRect(rect);

    //Get the games block height/width relative to the window height/width
    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;

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

//Accept the plant the user wants to plant next
void myView::acceptPlant(Plant *rPlant)
{
    //Get the plants pixmap
    QPixmap tempPix = rPlant->pixmap();
    //Create the pixmapItem
    item = new QGraphicsPixmapItem(tempPix);
}

void myView::sunSpawn()
{
    //Add a new sun.
    suns.push_back(new Sun(((this->random(0,ROWS-1))*gameBlockHeight +(gameBlockHeight/4)),(this->random(0,COLUMNS-1)*gameBlockWidth + (gameBlockWidth/4))));
    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);
}

//This is called whenever the user clicks on the screen.
void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;
    QPointF tempPoint = event->pos();
    if(mG->isPlantSelected){
        for(int i = 0; i < ROWS; i ++){
            for(int j = 0; j < COLUMNS; j++){
                //If the user clicks within a grid item AND that grid item isnt filled...
                if(grid[i][j].contains(event->pos()) && !gridFill[i][j]){
                    //Set the item position to the center of the grid.
                    item->setPos(grid[i][j].topLeft());
                    //Add the item to the scene.
                    scene->addItem(item);
                    gridFill[i][j] = true; //This grid space is now occupied.
                    mG->removeSunPoints(); // remove the sun points for this plant.
                }
            }
        }

    }else{
        //Itterate through all the current suns
        for(sunIter = suns.begin(); sunIter != suns.end();){
            //If the user clicks within the range of the sun...
            if((qAbs(tempPoint.x() - (*(*sunIter)).getLocation().x()) <= range) && (qAbs(tempPoint.y() - (*(*sunIter)).getLocation().y()) <= range)){
                //Delete the sun the user  clicks on
                delete *sunIter;
                //Erase the sun from the vector.
                sunIter = suns.erase(sunIter);
                //decrement the sun index as a sun was just removed.
                sunIndex --;
                //Add the sun points.
                mG->addSunPoints();
            }else{
                //Increase the sunIterator if no sun was removed.
                sunIter ++;
            }
        }
    }

}
