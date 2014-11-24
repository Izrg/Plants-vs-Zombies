#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>

myView::myView(QWidget *parent, mainGame *rMG) :
    QGraphicsView(parent)
{
    //Initialize Game Objects
    zombieObj = new QList<Zombie*>();

    zombieObj->append(new Regular(this));
    //...

    zombieGridList = new QList<QList<QGraphicsPixmapItem*>*>();
    for (int i = 0; i < ROWS; i++) zombieGridList->append(new QList<QGraphicsPixmapItem*>());

    maxZombies = 5; // Set the max number of zombies.
    currentZombies = 0; // No zombies spawned yet.

    grass = new Grass();

    sun = new Sun(this);

    //Set the main game object to the maingame class instance
    mG = rMG;

    //Set up the scene
    scene = new QGraphicsScene(this);
    setScene(scene);    

    //So the scene handles the advance functions
    scene->addItem(sun);
    scene->addItem(zombieObj->back());

    //Set up the timers
    moveTimer = new QTimer(this);
    sunTimer = new QTimer(this);
    zombieSpawnTimer = new QTimer(this);

    mapper = new QSignalMapper(this);
    zombieMapper = new QSignalMapper(this);

    //Start the move timer to control movement.
    connect(moveTimer, SIGNAL(timeout()), scene, SLOT(advance()));

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

    //Set up the game board.
    WIDTH = parent->width();
    HEIGHT = parent->height();

    //Set the size of the screen.
    QRectF rect(0,0,WIDTH,HEIGHT);
    setSceneRect(rect);

    //Get the games block height/width relative to the window height/width
    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;

    //Set up intial step counters
    for(int i = 0; i < ROWS; i ++){
        for (int j = 0; j < COLUMNS; j++){
            QGraphicsPixmapItem* g = scene->addPixmap(*grass->getGrass((i%2 == j%2)));
            g->setPos(j*gameBlockWidth, i*gameBlockHeight);

            //Add the new rectangle to the array to hold the grid.
            grid[i][j] = QRectF(g->pos(), QSize(gameBlockWidth, gameBlockHeight));
            gridFill[i][j] = false;
        }
    }

    sun->instances->append(scene->addPixmap(sun->pixmap()));
    sun->instances->back()->setPos(random(0, COLUMNS - 1) * gameBlockWidth + gameBlockWidth/4, 0);
    sun->onCreate(true, random(0, ROWS - 1));
}

//Returns a random number.
int myView::random(int x1, int x2)
{
    return qrand() % ((x2 + 1) - x1) + x1;
}

//This is called on a timer to spawn suns throughout the game every 10s
void myView::sunSpawn(QObject *rPoint)
{
    QPointF* p = (QPointF*)rPoint;
    int column;
    bool falling;
    //checks if the sun is falling or if it is being placed on a sunflower.
    if(falling = (p->x() == -1)) p = new QPointF((random(0, ROWS - 1)),(random(0, COLUMNS - 1)));
    //row = p->x() * gameBlockHeight +(gameBlockHeight/4);
    column = p->y() * gameBlockWidth + (gameBlockWidth/4);

    sun->instances->append(scene->addPixmap(sun->pixmap()));
    sun->instances->back()->setPos(column, 0);
    sun->onCreate(falling, random(0, ROWS - 1));
}

void myView::zombieEat(QObject *rPlant)
{
    //TODO
    /*
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
    */
}

//This is called to spawn zombies.
void myView::zombieSpawner()
{
    currentZombies ++; // One more zombie has spawned.
    //If the max zombies hasnt been reached yet...
    if(currentZombies <= maxZombies)
    {
        //Add a new zombie.
        int WHICH_ZOMBIE = 0;
        zombieObj->at(WHICH_ZOMBIE)->instances->append(scene->addPixmap(zombieObj->at(WHICH_ZOMBIE)->pixmap()));
        int row = random(0, ROWS - 1);
        zombieGridList->at(row)->append(zombieObj->at(WHICH_ZOMBIE)->instances->back());
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setPos(COLUMNS * gameBlockWidth, row * gameBlockHeight);
    }
}

//This is called whenever the user clicks on the screen.
void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;

    //If the user has selected to plant a plant
    if(mG->plantSelected > -1)
    {
        for(int i = 0; i < ROWS; i ++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                //If the user clicks within a grid item AND that grid item isnt filled...
                if(grid[i][j].contains(event->pos()) && !gridFill[i][j]){
                    // Plant the new plant.
                    mG->plantObj->at(mG->plantSelected)->instances->append(scene->addPixmap(mG->plantObj->at(mG->plantSelected)->pixmap()));
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setPos(j * gameBlockWidth, i * gameBlockHeight);
                    mG->plantObj->at(mG->plantSelected)->onPlant();

                    gridFill[i][j] = true; //This grid space is now occupied.
                    mG->removeSunPoints(mG->plantObj->at(mG->plantSelected)->getCost()); // remove the sun points for this plant.
                    mG->plantSelected = -1; // No more plant is selected.
                    QWidget::setCursor(Qt::ArrowCursor);

                    //TODO - Put in onPlant()
                    //(*plantsIter)->rateTimer->start((*plantsIter)->getRate() * 100); // Start the plant rateTimer based on the plants rate.
                }
            }
        }
        //If the user is currently not planting a plant.
    }else{

        for(int i = 0; i < sun->instances->size(); i++)
        {
            if((qAbs(event->pos().x() - sun->instances->at(i)->pos().x()) <= range) && (qAbs(event->pos().y() - sun->instances->at(i)->pos().y()) <= range))
            {
                mG->addSunPoints();
                delete sun->instances->at(i);
                sun->instances->removeAt(i--);
            }
        }
    }

}
