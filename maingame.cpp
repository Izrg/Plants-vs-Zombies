#include <QDebug>
#include <QMouseEvent>
#include <QLayout>

#include "maingame.h"
#include "ui_maingame.h"
#include "mainwindow.h"
#include "myview.h"

mainGame::mainGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    //Set UI
    ui->setupUi(this);
    //Add the Gameboard

    //Initialize Game Objects

    plantObj = new QList<Plant*>();
    plantObj->append(new Sunflower());
    plantObj->append(new Peashooter());

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
    SunPoints = 500;
    ui->sunPointsLbl->setText(QString("Sun Points: %1").arg(SunPoints));

    //Setup active Plant Buttons
    checkPlants();
}
//Add sun points when the user clicks a sun.
void mainGame::addSunPoints()
{
    //Add 25 sun points.
    SunPoints += 25;
    //Change the text of the sunPointsLbl.
    ui->sunPointsLbl->setText(QString("Sun Points: %1").arg(SunPoints));
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
    ui->sunPointsLbl->setText(QString("Sun Points: %1").arg(SunPoints));
}

void mainGame::checkPlants()
{
    for (int i = 0; i < plantObj->size(); i++)
    {
        if(plantObj->at(i)->getCost() <= SunPoints)
        {
            buttons->at(i)->setEnabled(true);
        }
    }
}

mainGame::~mainGame()
{
    delete ui;
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
    }
}
