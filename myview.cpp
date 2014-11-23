#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>
#include <QMovie>
#include <QAction>
myView::myView(QWidget *parent, mainGame *rMG) :
    QGraphicsView(parent)
{

    //Set up the game board.
    WIDTH = parent->width();
    HEIGHT = parent->height();
    //Set up the scene
    scene = new QGraphicsScene(this);
    setScene(scene);

    //Set the main game object to the maingame class instance
    mG = rMG;

    plantsIndex = 0; // Initilize the plants index to 0, no plants.
    zombieIndex = 0; // Initilize the zombies index to 0, no zombies.
    sunIndex = 0; //Initilize the sun index to 0, no suns.

    //Set up the timers
    moveTimer = new QTimer(this);
    sunTimer = new QTimer(this);
    zombieSpawnTimer = new QTimer(this);

    maxZombies = 5; // Set the max number of zombies.
    currentZombies = 0; // No zombies spawned yet.

    //Start the move timer to control movement.
    connect(moveTimer, SIGNAL(timeout()), this->scene, SLOT(advance()));


    //QAction* a1 = new QAction(this);
    mapper = new QSignalMapper(this);
    zombieMapper = new QSignalMapper(this);

    //Start the sun timer, which controls when suns spawn.
    connect(sunTimer, SIGNAL(timeout()), mapper, SLOT(map()));
    mapper->setMapping(sunTimer,(QObject*)new QPointF(-1,-1));
    connect(mapper,SIGNAL(mapped(QObject*)),this,SLOT(sunSpawn(QObject*)));

    //Start the zombie timer, which controls when zombies spawn.
    connect(zombieSpawnTimer, SIGNAL(timeout()),this,SLOT(zombieSpawner()));

    //Initiate the timers.
    sunTimer->start(10000);
    moveTimer->start(100);
    zombieSpawnTimer->start(5000);

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
    //g1 = new Grass(dark);
    //g2 = new Grass(!dark);
    //This loop is used to draw the grid.
    for(int i = 0; i < ROWS; i ++){
        for (int j = 0; j < COLUMNS; j++){
            g1 = new Grass(dark);
            dark = (!dark);
            //Set the new grid square.
            QRectF tempRect (widthStep,heightStep, gameBlockWidth, gameBlockHeight);
            //Add the new rectangle to the array to hold the grid.
            grid[i][j] = tempRect;
            //Add the grass texture to the grid.
            g1->setPos(widthStep,heightStep);
            scene->addItem(g1);
            widthStep += gameBlockWidth;

        }
        dark = (!dark);
        //Move down a row based on the block height.
        heightStep += gameBlockHeight;
        //Reset the width step to start drawing at he left side of screen again.
        widthStep = 0;
    }

    //Add an initial sun and add it to the scene.
    suns.push_back(new Sun(((this->random(0,ROWS-1))*gameBlockHeight +(gameBlockHeight/4)),(this->random(0,COLUMNS-1)*gameBlockWidth + (gameBlockWidth/4)),true));
    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);
}

//Returns a random number.
int myView::random(int x1, int x2)
{
    return qrand() % ((x2 + 1) - x1) + x1;
}

void myView::plantNewPlant()
{
    //Pushes a new plant into the plants vector
    plants.push_back(mG->getPlant());
    plantsIter = plants.begin() + plantsIndex;
    plantsIndex ++; // Increase plants index as a plant was just planted.
    //Loads the new plants pixmap
    QPixmap tempPix;
    tempPix.load((*plantsIter)->getImagePath());
    tempPix.scaled(W,W); // Scale the image to desired size
    //Sets the new plants pixmap
    (*plantsIter)->setImage(tempPix);
}

//This is called on a timer to spawn suns throughout the game every 10s
void myView::sunSpawn(QObject *rPoint)
{
    QPointF* p = (QPointF*)rPoint;
    int row, column;
    bool falling;
    //checks if the sun is falling or if it is being placed on a sunflower.
    if(falling = (p->x() == -1)) p = new QPointF((this->random(0,ROWS-1)),(this->random(0,COLUMNS -1)));
    row = p->x() * gameBlockHeight +(gameBlockHeight/4);
    column = p->y() * gameBlockWidth + (gameBlockWidth/4);

    //Spawns a sun at a random column.
    //The sun then drops to a random row.
    suns.push_back(new Sun(row,column, falling));
    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);
}

void myView::zombieEat(QObject *rPlant)
{
    QPointF* p = (QPointF*)rPlant;

    for(plantsIter = plants.begin(); plantsIter != plants.end();plantsIter ++){
        //Check for which plant is being eaten
        if(((Plant*)(*plantsIter))->pos() == *p){
            ((Plant*)(*plantsIter))->setLife((((Plant*)(*plantsIter))->getLife()) - 1);
        }
        //if the plants life is 0
        if((Plant*)(*plantsIter)->getLife() <= 0){
            for(int i = 0; i < ROWS; i ++){
                for(int j = 0; j < COLUMNS; j++){
                    //make the grid section the plant was on free to be planted on again.
                    if(grid[i][j].contains(((Plant*)(*plantsIter))->pos())){
                        gridFill[i][j] = false; //This grid space is now free to be planted in
                    }
                }
            }
            //Delete the plant and remove it from the vector
            delete *plantsIter;
            plantsIter = plants.erase(plantsIter);
            //Decrement plant index
            plantsIndex --;

            return;
        }
    }
    //qDebug() << "Plant Health : " << tempPlant->getLife() << endl;
}

//This is called to spawn zombies.
void myView::zombieSpawner()
{
    currentZombies ++; // One more zombie has spawned.
    //If the max zombies hasnt been reached yet...
    if(currentZombies <= maxZombies){
        //Add a new zombie.
        zombies.push_back(new Regular(((this->random(0,ROWS-1))*gameBlockHeight),COLUMNS *gameBlockWidth,this));
        zombieIter = zombies.begin() + zombieIndex;
        zombieIndex ++;
        scene->addItem(*zombieIter);
    }else{
        return;
    }


}

//This is called whenever the user clicks on the screen.
void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;
    QPointF tempPoint = event->pos();
    //If the user has selected to plant a plant
    if(mG->isPlantSelected){
        for(int i = 0; i < ROWS; i ++){
            for(int j = 0; j < COLUMNS; j++){
                //If the user clicks within a grid item AND that grid item isnt filled...
                if(grid[i][j].contains(event->pos()) && !gridFill[i][j]){
                    plantNewPlant(); // Plant the new plant.
                    (*plantsIter)->setPlantLocation(i,j); // Set the plants location.
                    (*plantsIter)->onPlant(); // Initiate the on plant funciton.
                    //Set the item position to the center of the grid.
                    //Add the plant to the scene
                    ((Plant*)(*plantsIter))->setPos(grid[i][j].topLeft());
                    scene->addItem(*plantsIter);
                    gridFill[i][j] = true; //This grid space is now occupied.
                    mG->removeSunPoints((*plantsIter)->getCost()); // remove the sun points for this plant.
                    mG->isPlantSelected = false; // No more plant is selected.
                    (*plantsIter)->rateTimer->start((*plantsIter)->getRate() * 100); // Start the plant rateTimer based on the plants rate.
                }
            }
        }
        //If the user is currently not planting a plant.
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
