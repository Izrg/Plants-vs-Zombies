#include "myview.h"
#include <qdebug.h>
#include <QMouseEvent>

myView::myView(QWidget *parent, mainGame *rMG) :
    QGraphicsView(parent)
{
    //Initialize Game Objects
    zombieObj = new QList<Zombie*>();

    zombieObj->append(new Regular());
    //...

    zombieGridList = new QList<QList<QGraphicsPixmapItem*>*>();
    for (int i = 0; i < ROWS; i++) zombieGridList->append(new QList<QGraphicsPixmapItem*>());

    maxZombies = 2; // Set the max number of zombies.
    currentZombies = 0; // No zombies spawned yet.

    grass = new Grass();

    sun = new Sun(this);
    bullet = new Bullet(this);

    //Set the main game object to the maingame class instance
    mG = rMG;

    //Set up the scene
    scene = new QGraphicsScene(this);
    setScene(scene);

    //So the scene handles the advance functions
    scene->addItem(sun);
    scene->addItem(bullet);

    for(int i = 0; i < zombieObj->size(); i++){
        scene->addItem(zombieObj->at(i));

    }
    scene->addItem(zombieObj->back());

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
            plantGrid[i][j] = NULL;
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
    //qDebug() << falling << endl;
    sun->instances->append(scene->addPixmap(sun->pixmap()));
    sun->instances->back()->setPos(column, 0);
    sun->onCreate(falling, random(0, ROWS - 1));
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
                qDebug() << "Plant object Index: " << plantObjectIndex << endl;
                qDebug() << "plant Instance Index: " << plantInstanceIndex << endl;
                //Set the plant grid location to NULL
                plantGrid[zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt()][i] = NULL;
                //Delete this plant.
                //Reset the zombies flag
                delete plantObj->at(plantObjectIndex)->instances->at(plantInstanceIndex);
                plantObj->at(plantObjectIndex)->instances->removeAt(plantInstanceIndex);

                //Go through all the plant objects of the type of plant that was just deleted.
                for(int j = 0; j < plantObj->at(plantObjectIndex)->instances->size(); j++)
                {
                    int temp;
                    //If a specific instance of the plant is larger than the one just erased, push it back 1.
                    if((temp = plantObj->at(plantObjectIndex)->instances->at(j)->data(PvZ::INSTANCE_INDEX).toInt()) > plantInstanceIndex)
                    {
                        plantObj->at(plantObjectIndex)->instances->at(j)->setData(PvZ::INSTANCE_INDEX,QVariant(temp - 1));
                    }
                }
                zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setFlag(QGraphicsItem::ItemIsMovable,false);
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

void myView::damageZombie(int zombieObjectIndex, int zombieInstanceIndex,int damage, bool slow)
{
    int tempLife = zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::INSTANCE_LIFE).toInt();
    tempLife -= damage;

    if(slow){
        qDebug() << "Slow shot!" << endl;
    }

    if(tempLife <= 0)
    {
        //Remove the zombie from the gridlist.
        zombieGridList->at(zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->data(PvZ::ROW_INDEX).toInt())->removeAt(zombieInstanceIndex);
        //Go through the zombies and decrement their instance by 1 as a zombie was just killed.
        for(int j = 0; j < zombieObj->at(zombieObjectIndex)->instances->size(); j++)
        {
            int temp;
            //If a specific instance of the zombie is larger than the one just erased, push it back 1.
            qDebug() << "Next zombie instance : " << zombieObj->at(zombieObjectIndex)->instances->at(j)->data(PvZ::INSTANCE_INDEX).toInt() << endl;
            if((temp = zombieObj->at(zombieObjectIndex)->instances->at(j)->data(PvZ::INSTANCE_INDEX).toInt()) > zombieInstanceIndex)
            {
                temp --;
                zombieObj->at(zombieObjectIndex)->instances->at(j)->setData(PvZ::INSTANCE_INDEX,QVariant(temp));
            }
        }
        delete zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex);
        zombieObj->at(zombieObjectIndex)->instances->removeAt(zombieInstanceIndex);
        //Go through all the plant objects of the type of plant that was just deleted.
        return;

    }
    //Set the zombies new health.
    zombieObj->at(zombieObjectIndex)->instances->at(zombieInstanceIndex)->setData(PvZ::INSTANCE_LIFE,QVariant(tempLife));

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
        //Saves the zombie type to the zombie grid list.
        zombieGridList->at(row)->back()->setData(PvZ::ZOMBIE_TYPE,QVariant(WHICH_ZOMBIE));
        zombieGridList->at(row)->back()->setData(PvZ::INSTANCE_INDEX,QVariant(zombieObj->at(WHICH_ZOMBIE)->instances->size() - 1));

        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::Z_SPEED,QVariant(zombieObj->at(WHICH_ZOMBIE)->speed));

        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setPos(COLUMNS * gameBlockWidth, row * gameBlockHeight);
        //Set the zombies class type.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::CLASS_TYPE,QVariant('Z'));
        //Set the zombie instance.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::INSTANCE_INDEX,QVariant(zombieObj->at(WHICH_ZOMBIE)->instances->size() - 1));
        /*
         * TODO:
         * NEED TO CHANGE THE "ZOMBIE TYPE" TO BE WHATEVER ZOMBIE HAS SPAWNED
         * E.G, 0 = Regular Zombie, 1 = Conehead, etc...
         *
         */
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::ZOMBIE_TYPE,QVariant(0));
        //Set the zombie ='s rate index instance to 0;
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::RATE_INDEX,QVariant(0));
        //Add the row of the current zombie instance to the Row index
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::ROW_INDEX,QVariant(row));
        //Set this zombie instance health to Zombie health + its equipment health
        //zombieObj->at(WHICH_ZOMBIE)->instanceLife->append((zombieObj->at(WHICH_ZOMBIE)->zombieLife) + (zombieObj->at(WHICH_ZOMBIE)->equipmentLife));
        int tempLife = zombieObj->at(WHICH_ZOMBIE)->zombieLife + zombieObj->at(WHICH_ZOMBIE)->equipmentLife;
        //Set the zombie instance life index with the zombies health.
        zombieObj->at(WHICH_ZOMBIE)->instances->back()->setData(PvZ::INSTANCE_LIFE,QVariant(tempLife));

        //Call zombie on spawn function.
        zombieObj->at(WHICH_ZOMBIE)->onSpawn(this);
    }
}

//This is called whenever the user clicks on the screen.
void myView::mousePressEvent(QMouseEvent *event)
{
    int range = Sun::W;

    //If the user has selected to plant a plant
    if(mG->plantSelected > -1)
    {
        for(int i = 0; i < ROWS; i++)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                //If the user clicks within a grid item AND that grid item isnt filled...
                if(grid[i][j].contains(event->pos()) && (plantGrid[i][j] == NULL)){
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
