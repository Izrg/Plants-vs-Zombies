#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>

extern QList<QObject*> *flowerSuns;
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList = new QList<QList<QGraphicsPixmapItem*>*>();

myView::myView(QWidget *parent, mainGame *rMG) :
    QGraphicsView(parent)
{
    //Set up the game board.
    WIDTH = parent->width();
    HEIGHT = parent->height();

    //Set the main game object to the maingame class instance
    mG = rMG;

    //Initialize Game Objects
    zombieObj = new QList<Zombie*>();

    zombieObj->append(new Regular());
    zombieObj->append(new Flag());
    zombieObj->append(new Conehead());
    zombieObj->append(new Buckethead());
    zombieObj->append(new Newspaper());
    //...


    for (int i = 0; i < ROWS; i++) zombieGridList->append(new QList<QGraphicsPixmapItem*>());

    maxZombies = mG->maxZombies; // Set the max number of zombies.
    //maxZombies = 2;
    currentZombies = 0; // No zombies spawned yet.
    zombieSequenceIndex = 0; //Stores the sequence index of the zombies.
    //The gambe board tiles.
    grass = new Grass();
    dirt = new Dirt();
    lawnmower = new Lawnmower();

    sun = new Sun(HEIGHT/ROWS);
    bullet = new Bullet(this);


    //Set up the scene
    scene = new QGraphicsScene(this);
    setScene(scene);

    //So the scene handles the advance functions
    scene->addItem(sun);
    scene->addItem(bullet);
    scene->addItem(lawnmower);

    for(int i = 0; i < zombieObj->size(); i++){
        scene->addItem(zombieObj->at(i));
    }

    for(int i = 0; i < mG->plantObj->size(); i++){
        scene->addItem(mG->plantObj->at(i));
    }

    //Set up the timers
    moveTimer = new QTimer(this);
    sunTimer = new QTimer(this);
    zombieSpawnTimer = new QTimer(this);

    mapper = new QSignalMapper(this);
    zombieMapper = new QSignalMapper(this);

    //Start the move timer to control movement.
    connect(moveTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(sunflowerSun()));

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

    //Set the size of the screen.
    QRectF rect(0,0,WIDTH,HEIGHT);
    setSceneRect(rect);

    //Get the games block height/width relative to the window height/width
    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;

    //Set up the grass
    for(int i = 0; i < ROWS; i ++)
    {
        //Based on the active rows, put grass or dirt
        if((mG->activeRow == 1 && i == 2) || (mG->activeRow == 3 && (i == 1 || i == 2 || i == 3)) || mG->activeRow == 5)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                QGraphicsPixmapItem* g = scene->addPixmap(*grass->getGrass((i%2 == j%2)));
                g->setPos(j*gameBlockWidth, i*gameBlockHeight);
                //Add the new rectangle to the array to hold the grid.
                grid[i][j] = QRectF(g->pos(), QSize(gameBlockWidth, gameBlockHeight));
                plantGrid[i][j] = NULL;
            }
            for(int j = 0; j < COLUMNS; j++)
            {
                if(j == 0)
                {
                    //Add lawnmowers.
                    lawnmower->instances->append(plantGrid[i][j] = scene->addPixmap(lawnmower->pixmap()));
                    lawnmower->instances->back()->setPos(j*gameBlockWidth,i*gameBlockHeight);
                    lawnmower->instances->back()->setData(PvZ::ROW_INDEX,QVariant(i));
                    lawnmower->instances->back()->setData(PvZ::COLUMN_INDEX,QVariant(j));
                    lawnmower->onPlant(this);
                }
            }
        }else
        {
            //Put dirt if this isnt an active row.
            for (int j = 0; j < COLUMNS; j++)
            {

                QGraphicsPixmapItem* g = scene->addPixmap(*dirt->getDirt());
                g->setPos(j*gameBlockWidth, i*gameBlockHeight);

                //Add the new rectangle to the array to hold the grid.
                grid[i][j] = QRectF(g->pos(), QSize(gameBlockWidth, gameBlockHeight));
                //This are in the grrid is false as there is dirt.
                plantGrid[i][j] = dirt;
            }
        }

    }

    sun->instances->append(scene->addPixmap(sun->pixmap()));
    sun->instances->back()->setPos(random(0, COLUMNS - 1) * gameBlockWidth + gameBlockWidth/4,0);
    sun->onCreate(true, random(0, ROWS - 1));
}

void myView::levelLost()
{
    mG->levelLost();
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
    bool falling;
    //checks if the sun is falling or if it is being placed on a sunflower.
    if(falling = (p->x() == -1))
    {
        p = new QPointF((random(0, ROWS - 1)),(random(0, COLUMNS - 1)));
        p->setX(p->x() * gameBlockHeight);
        p->setY(p->y() * gameBlockWidth);
    }
    p->setX(p->x() + (gameBlockHeight/4));
    p->setY(p->y() + (gameBlockWidth/4));
    sun->instances->append(scene->addPixmap(sun->pixmap()));
    sun->instances->back()->setPos(p->y(), falling ? 0 : p->x());
    sun->onCreate(falling, random(0, ROWS - 1));
}

void myView::sunflowerSun()
{
    while(!flowerSuns->isEmpty())
    {
        sunSpawn(flowerSuns->back());
        flowerSuns->pop_back();
    }
}

//This method is called when zombies eat plant brains.
//IF MORE TAHN ONE ZOMBIE EATING SAME PLANT, ONLY THE ONE WHO KILLS IT KEEPS MOVING!!!!! GOTTA FIX!!
void myView::zombieEat(int zombieObjectIndex, int zombieInstanceIndex)
{
    //plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::rowIndex).toInt()][i]

    for(int i = 0; i < COLUMNS; i++)
    {
        //If There is no plant in this current location, continue to top of loop.
        if((plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i]) == NULL) continue;

        if((plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i])->collidesWithItem(zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)))
        {
            //Get the plants life
            int tempLife = plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i]->data(PvZ::INSTANCE_LIFE).toInt();
            //Subtract the zombies attack.
            tempLife -= zombieObj->at(zombieObjectIndex)->attack;
            qDebug() << "Plant Health: " << tempLife << endl;
            //If the health is below 0
            if(tempLife <= 0)
            {
                int plantObjectIndex = (plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i])->data(PvZ::PLANT_TYPE).toInt();
                int plantInstanceIndex = (plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i])->data(PvZ::INSTANCE_INDEX).toInt();

                //Set the plant grid location to NULL
                plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i] = NULL;
                //Delete this plant.
                //Destroy this plant instance.
                plantObj->at(plantObjectIndex)->destroy(plantInstanceIndex);

                //Update instances
                for(int j = 0; j < mG->plantObj->at(plantObjectIndex)->instances->size(); j++) mG->plantObj->at(plantObjectIndex)->instances->at(j)->setData(PvZ::INSTANCE_INDEX, j);
                //Reset the zombie flag.
                //zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setFlag(QGraphicsItem::ItemIsMovable,false);
                return;
            }
            //Set the new health of the plant.
            plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i]->setData(PvZ::INSTANCE_LIFE,QVariant(tempLife));
        }
    }
}

void myView::plantShoot(int plantObjectType, int plantInstanceIndex, bool slow)
{
    bullet->instances->append(scene->addPixmap(*bullet->getBullet(slow)));
    //Set the position of the bullet to the plant that shot it.
    bullet->instances->back()->setPos(plantObj->at(plantObjectType)->instances->at(plantInstanceIndex)->pos().x() + 40,plantObj->at(plantObjectType)->instances->at(plantInstanceIndex)->pos().y());
    bullet->instances->back()->setData(PvZ::ROW_INDEX,QVariant(plantObj->at(plantObjectType)->instances->at(plantInstanceIndex)->data(PvZ::ROW_INDEX).toInt()));
    bullet->instances->back()->setData(PvZ::INSTANCE_DAMAGE,QVariant(plantObj->at(plantObjectType)->instances->at(plantInstanceIndex)->data(PvZ::INSTANCE_DAMAGE).toInt()));
    bullet->instances->back()->setData(PvZ::PLANT_TYPE,QVariant(plantObjectType));
    bullet->instances->back()->setData(PvZ::INSTANCE_INDEX,QVariant(plantObj->at(plantObjectType)->instances->at(plantInstanceIndex)->data(PvZ::INSTANCE_INDEX).toInt()));
}

void myView::damageZombie(int zombieObjectIndex, int zombieInstanceIndex, int zombieGridInstance, int damage, bool slow)
{

    int tempLife = zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::INSTANCE_LIFE).toInt();
    int row = zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt();
    tempLife -= damage;
    //qDebug() << "Zombie Object: " << zombieObjectIndex << endl;
    //qDebug() << "Zombie Instance: " << zombieInstanceIndex << endl;
    if(slow)
    {
        //Check a zombie slowed flag.
        if(!zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->flags().testFlag(QGraphicsItem::ItemIsPanel))
        {
            //CHANGE ZOMBIE COLOR HERE!!!!!
            //Set a zombie slowed flag.
            zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setFlag(QGraphicsItem::ItemIsPanel, true);
            qDebug() << "Before Speed: " << zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::Z_SPEED).toDouble() << endl;
            zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setData(PvZ::Z_SPEED,QVariant(zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::Z_SPEED).toDouble() * 0.5));
            qDebug() << "After Speed: " << zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::Z_SPEED).toDouble() << endl;
            zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setData(PvZ::RATE_INDEX,QVariant(zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::RATE_INDEX).toDouble() * 0.5));

        }
    }


    if(tempLife <= 0)
    {
        //Remove from scene
        scene->removeItem(zombieGridList->at(row)->at(zombieGridInstance));

        //Delete the object in the heap
        delete zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex);
        zombieObj->at(zombieObjectIndex)->instances->removeAt(zombieInstanceIndex);

        //Remove the zombie from the gridlist.
        qDebug() << "Row: " <<  row << endl;
        qDebug() << "Size Before: " << zombieGridList->at(row)->size() << endl;
        zombieGridList->at(row)->removeAt(zombieGridInstance);
        qDebug() << "Size After: " << zombieGridList->at(row)->size() << endl;

        //zombieGridList->at(zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt())
        //Destroy this zombie instance.
        //zombieObj->at(zombieObjectIndex)->destroy(zombieInstanceIndex);

        //Update instances
        for(int j = 0; j < zombieObj->at(zombieObjectIndex)->instances->size(); j++) zombieObj->at(zombieObjectIndex)->instances->at(j)->setData(PvZ::INSTANCE_INDEX, j);

        return;

    }
    //Set the zombies new health.
    zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setData(PvZ::INSTANCE_LIFE,QVariant(tempLife));

}

void myView::destroyPlant(int row, int column)
{
    scene->removeItem(plantGrid[row][column]);
    int obj = plantGrid[row][column]->data(PvZ::PLANT_TYPE).toInt();
    (mG->plantObj->at(obj))->destroy(plantGrid[row][column]->data(PvZ::INSTANCE_INDEX).toInt());
    plantGrid[row][column] = NULL;

    //Update instances
    for(int i = 0; i < mG->plantObj->at(obj)->instances->size(); i++) mG->plantObj->at(obj)->instances->at(i)->setData(PvZ::INSTANCE_INDEX, i);

}
//This is called to spawn zombies.
void myView::zombieSpawner()
{
    currentZombies ++; // One more zombie has spawned.
    int row;
    //If the max zombies hasnt been reached yet...
    if(currentZombies <= maxZombies)
    {

        //Add a new zombie.
        int WHICH_ZOMBIE = (mG->sequence.at(zombieSequenceIndex) - 1); // Spawn the zombie of type from the given sequence.
        //int WHICH_ZOMBIE = 4;
        zombieSequenceIndex ++; // Increement the sequence index

        zombieObj->at(WHICH_ZOMBIE)->instances->append(scene->addPixmap(zombieObj->at(WHICH_ZOMBIE)->pixmap()));
        if(mG->activeRow == 1)
        {
           row = random(2, 2);
        }else if(mG->activeRow == 3)
        {
            row = random(1, 3);
        }else row = random(0, ROWS - 1);

        zombieGridList->at(row)->append(zombieObj->at(WHICH_ZOMBIE)->instances->back());
        //Saves the zombie type to the zombie grid list.
        zombieGridList->at(row)->back()->setData(PvZ::ZOMBIE_TYPE,QVariant(WHICH_ZOMBIE));
        zombieGridList->at(row)->back()->setData(PvZ::INSTANCE_INDEX,QVariant(zombieObj->at(WHICH_ZOMBIE)->instances->size() - 1));

        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::Z_SPEED,QVariant(zombieObj->at(WHICH_ZOMBIE)->speed));

        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setPos(COLUMNS * gameBlockWidth, row * gameBlockHeight);
        //Set the zombies class type.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::CLASS_TYPE,QVariant('Z'));
        //Set the zombie instance.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::INSTANCE_INDEX,QVariant(zombieObj->at(WHICH_ZOMBIE)->instances->size() - 1));

        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::ZOMBIE_TYPE,QVariant(WHICH_ZOMBIE));
        //Set the zombie ='s rate index instance to 0;
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::RATE_INDEX,QVariant(0));
        //Add the row of the current zombie instance to the Row index
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::ROW_INDEX,QVariant(row));
        //Set this zombie instance health to Zombie health + its equipment health
        int tempLife = zombieObj->at(WHICH_ZOMBIE)->zombieLife + zombieObj->at(WHICH_ZOMBIE)->equipmentLife;
        //Set the zombie instance life index with the zombies health.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::INSTANCE_LIFE,QVariant(tempLife));

        //Call zombie on spawn function.
        zombieObj->at(WHICH_ZOMBIE)->onSpawn(this);
    }else
    {
        for(int i = 0; i < ROWS; i++) if(!zombieGridList->at(i)->isEmpty()) return;
        mG->levelWon(); // Call the level won function.

    }
}

//This is called whenever the user clicks on the screen.
void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;
    //Called if the user has the shovel.
    if(mG->plantSelected ==-2)
    {
        //Convert Point from mouse into COLUMN, ROW
        QPoint gridCoords = event->pos();
        int c = -1;
        for (int v = gridCoords.x(); v > 0; c++) v -= gameBlockWidth;
        gridCoords.setX(c);
        c = -1;
        for (int v = gridCoords.y(); v > 0; c++) v -= gameBlockHeight;
        gridCoords.setY(c);

        if(plantGrid[gridCoords.y()][gridCoords.x()] != NULL)
        {
            destroyPlant(gridCoords.y(), gridCoords.x());
            if(!mG->shovelLock)
            {
                mG->plantSelected = -1;
                QWidget::setCursor(Qt::ArrowCursor);
            }
        }
        return;
    }
    //If the user has selected to plant a plant
    if(mG->plantSelected > -1)
    {
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                bool repeater = false;
                //If the user clicks within a grid item AND that grid item isnt filled...
                if((grid[i][j].contains(event->pos()) && (plantGrid[i][j] == NULL)) || (repeater = ((grid[i][j].contains(event->pos())) && (mG->plantSelected == 7) && (plantGrid[i][j] != NULL) && (plantGrid[i][j]->data(PvZ::PLANT_TYPE).toInt() == 1)))){
                    if(repeater)
                    {
                        //Destroy the peashooter that was there before.
                        scene->removeItem(plantGrid[i][j]);
                        int obj = plantGrid[i][j]->data(PvZ::PLANT_TYPE).toInt();
                        (mG->plantObj->at(obj))->destroy(plantGrid[i][j]->data(PvZ::INSTANCE_INDEX).toInt());
                        plantGrid[i][j] = NULL;
                        //Update instances.
                        for(int i = 0; i < mG->plantObj->at(obj)->instances->size(); i++) mG->plantObj->at(obj)->instances->at(i)->setData(PvZ::INSTANCE_INDEX, i);

                    }else{
                        //Return if the user is trying to plant a repeater invalidly
                        if(mG->plantSelected == 7)  return;
                    }
                    // Plant the new plant.
                    mG->plantObj->at(mG->plantSelected)->instances->append(plantGrid[i][j] = scene->addPixmap(mG->plantObj->at(mG->plantSelected)->pixmap()));
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setPos(j * gameBlockWidth, i * gameBlockHeight);

                    //Save this plants instance number
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::INSTANCE_INDEX, QVariant(mG->plantObj->at(mG->plantSelected)->instances->size() - 1));
                    plantGrid[i][j]->setData(PvZ::INSTANCE_INDEX, QVariant(mG->plantObj->at(mG->plantSelected)->instances->size() - 1));
                    //Sets the plant slow data.
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::INSTANCE_SLOW,QVariant(mG->plantObj->at(mG->plantSelected)->slow));

                    //Sets the plant type e.g; 0 = Sunflower, 1 = peashooter etc..
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::PLANT_TYPE,QVariant(mG->plantSelected));
                    plantGrid[i][j]->setData(PvZ::PLANT_TYPE, QVariant(mG->plantSelected));
                    //Sets the plants damage.
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::INSTANCE_DAMAGE,QVariant(mG->plantObj->at(mG->plantSelected)->damage));

                    //Sets the plants class type.
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::CLASS_TYPE,QVariant('P'));
                    plantGrid[i][j]->setData(PvZ::CLASS_TYPE, QVariant('P'));

                    //Sets the plants rateindex to 0.
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::RATE_INDEX,QVariant(0));

                    //Set the plants instance life
                    //WALLNUT HERE
                    //mG->plantObj->at(mG->plantSelected)->instanceLife->append(mG->plantObj->at(mG->plantSelected)->life);
                    //Saves the instance life in the plants data.
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::INSTANCE_LIFE,QVariant(mG->plantObj->at(mG->plantSelected)->life));
                    plantGrid[i][j]->setData(PvZ::INSTANCE_LIFE, QVariant(mG->plantObj->at(mG->plantSelected)->life));

                    //Sets the plants Row: i and Column: j
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::ROW_INDEX,QVariant(i));
                    mG->plantObj->at(mG->plantSelected)->instances->back()->setData(PvZ::COLUMN_INDEX,QVariant(j));

                    //Calls the plants onPLant function
                    mG->plantObj->at(mG->plantSelected)->onPlant(this);

                    mG->removeSunPoints(mG->plantObj->at(mG->plantSelected)->getCost()); // remove the sun points for this plant.
                    mG->plantSelected = -1; // No more plant is selected.
                    QWidget::setCursor(Qt::ArrowCursor);

                }
            }
        }
        //If the user is currently not planting a plant.
    }else{
        int size = sun->instances->size();
        for(int i = 0; i < size; i++)
        {

            if(QRectF(sun->instances->at(i)->pos(), QSize(Sun::W, Sun::W)).contains(event->pos()))
            {
                mG->addSunPoints();
                scene->removeItem(sun->instances->at(i));
                sun->destroy(i--);
                size --;

            }
        }
        return;
    }

}
