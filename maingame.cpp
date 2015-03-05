#include <QDebug>
#include <QMouseEvent>
#include <QLayout>
#include <QMessageBox>
#include <QTime>
#include "maingame.h"
#include "ui_maingame.h"
#include "mainwindow.h"
#include "myview.h"
#include "fparcer.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;


mainGame::mainGame(QWidget *parent, MainWindow *rMW) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    mW = rMW;
    //Set UI
    ui->setupUi(this);


    QString tempFile = QCoreApplication::applicationDirPath() + "/pvz_levels.csv";
    if(tempFile == NULL)
    {
        QMessageBox::about(this,"Error","Warning, critical level file not found!");

    }

    levelParce = new Fparcer(tempFile,mW->userLvl);
    levelParce->readFile(false);


    //Initialize Game Objects
    plantObj = new QList<Plant*>();
    plantObj->append(new Sunflower());
    plantObj->append(new Peashooter());
    plantObj->last()->slow = false;
    plantObj->append(new Wallnut());
    plantObj->append(new Snowpea());
    plantObj->last()->slow = true;
    plantObj->append(new Chomper());
    plantObj->append(new Cherrybomb());
    plantObj->append(new PotatoMine());
    plantObj->append(new Repeater());

    //Set the basic level information based on what was read from the file.
    activeRow = levelParce->rows;
    sequence = levelParce->sequence;
    maxZombies = sequence.size();
    startTime = levelParce->startTime;
    interval = levelParce->interval;
    decrement = levelParce->decrement;

    name = mW->lastUser; // Save the user name;
    currentLevel = mW->userLvl;

    mV = new myView(ui->gameBoard,this);
    mV->plantObj = plantObj;

    buttons = new QList<QToolButton*>();

    mapper = new QSignalMapper(this);

    for (int i = 0; i < plantObj->size(); i++)
    {
        //Set up a Plant Button
        buttons->append(new QToolButton());
        buttons->back()->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        buttons->back()->setText(plantObj->at(i)->name);
        buttons->back()->setFixedHeight(91);
        buttons->back()->setFixedWidth(71);
        buttons->back()->setAutoFillBackground(true);
        buttons->back()->setIcon(QIcon(plantObj->at(i)->pixmap()));
        buttons->back()->setIconSize(QSize(W,W));
        buttons->back()->setToolTip(plantObj->at(i)->name);
        buttons->back()->setEnabled(false);

        //Map the Button onClick()
        connect(buttons->back(), SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(buttons->back(), i);

        //Add it to the UI
        ui->horizontalLayout->addWidget(buttons->back());
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(onPlantButtonClicked(int)));
    //Add a nice spacer to pretty things up
    QSpacerItem *item = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->horizontalLayout->addSpacerItem(item);

    //Initialize to "false" since no plant is selected.
    plantSelected = -1;

    //Initialize Sunpoints
    SunPoints = 50000;
    ui->sunPointsLbl->setText(QString("%1").arg(SunPoints));

    isPaused = false; // used to keep track if the user pauses the game.
    //Setup active Plant Buttons
    checkPlants();
}
//Add sun points when the user clicks a sun.
void mainGame::addSunPoints()
{
    //Add 25 sun points.
    SunPoints += 25;
    //Change the text of the sunPointsLbl.
    ui->sunPointsLbl->setText(QString("%1").arg(SunPoints));
    //Check which plants can now be planted with the new sun points.
    checkPlants();
}
//removes sun points after a user clicks a sun.
void mainGame::removeSunPoints(int rPoints)
{
    //remove the cost of the plant just planted.
    SunPoints -= rPoints;
    //check which plants can now be planted with the new sun points.
    checkPlants();

    //Change the text of the sunpointslbl
    ui->sunPointsLbl->setText(QString("%1").arg(SunPoints));
}

void mainGame::checkPlants()
{
    for (int i = 0; i < plantObj->size(); i++)
    {
        if(plantObj->at(i)->getCost() <= SunPoints) buttons->at(i)->setEnabled(true);
        else buttons->at(i)->setEnabled(false);
    }
}

mainGame::~mainGame()
{
    delete mV; // Delete the previous myview object.
    delete ui;
}

void mainGame::levelWon()
{
    mW->userLvl ++; // Increment the user level.
    mW->restartGame();
}

void mainGame::levelLost()
{
    mW->restartGame();
}

void mainGame::onPlantButtonClicked(int index)
{

    //If clicking on the same Plant, put it back
    if(plantSelected == index)
    {
        plantSelected = -1;
        mV->QWidget::setCursor(Qt::ArrowCursor);
        return;
    }

    //Note which Plant is selected
    plantSelected = index;
    mV->QWidget::setCursor(QCursor(plantObj->at(index)->pixmap()));
}

void mainGame::keyPressEvent(QKeyEvent *mouseEvent)
{
    switch(mouseEvent->key()){
    case Qt::Key_Escape:
        if(plantSelected != -1)
        {
            //Reset the cursor
            mV->QWidget::setCursor(Qt::ArrowCursor);
            //sets the plant selected to false.
            plantSelected = -1;
            break;
        }
    case Qt::Key_Control:
    {
        shovelLock = !shovelLock;
        break;
    }
    }
}

void mainGame::on_shovelButton_clicked()
{
    if(plantSelected == -2)
    {
        //Reset the cursor
        mV->QWidget::setCursor(Qt::ArrowCursor);
        //sets the plant selected to false.
        plantSelected = -1;
        shovelLock = false;
        return;
    }
    plantSelected = -2;
    mV->QWidget::setCursor(QCursor(QPixmap(":/Shovel/Shovel.png").scaled(40,40)));
}

void mainGame::on_menuBtn_clicked()
{

    if(!isPaused)
    {
        isPaused = true; //Game is now paused.
    }else{
        isPaused = false; // Not paused anymore
        pM->deleteLater();
    }

    //Stop all the active timers to pause the game.
    //Or resume them on second key press.
    if(isPaused)
    {
        mV->moveTimer->stop();
        mV->zombieSpawnTimer->stop();
        mV->sunTimer->stop();
        //Set all the buttons to disabled.
        for (int i = 0; i < plantObj->size(); i++)
        {
            buttons->at(i)->setEnabled(false);
        }
        ui->menuBtn->setEnabled(false);

        pM = new PauseMenu(0,this);
        pM->show();
    }else
    {
        mV->zombieSpawnTimer->start();
        mV->moveTimer->start();
        mV->sunTimer->start();
        ui->menuBtn->setEnabled(true);
        checkPlants();
        delete pM; // Delete the pause menu instance.
    }

}
