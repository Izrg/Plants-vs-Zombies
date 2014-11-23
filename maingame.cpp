#include "maingame.h"
#include "ui_maingame.h"
#include "sunflower.h"
#include "peashooter.h"
#include <mainwindow.h>
#include <sun.h>
#include <myview.h>
#include <qdebug.h>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QtGlobal>
#include <QTime>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPushButton>
QGraphicsView *gB;
QLabel *sunPointsLbl;
QPushButton *sunFlowerBtn;
QPushButton *peaShooterBtn;

static int sunPoints = 500; // Initilize the sun points.

mainGame::mainGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    mV = new myView(ui->gameBoard,this);

    //Set up the points label.
    sunPointsLbl = ui->sunPointsLbl;
    //Set up the sunflower
    sunFlowerBtn = ui->sunflowerBtn;
    //Set up the pea shooter
    peaShooterBtn = ui->peashooterBtn;

    //Initialize to false since no plant is selected.
    isPlantSelected = false;

    //Initially disable the buttons
    sunFlowerBtn->setEnabled(false);
    peaShooterBtn->setEnabled(false);

    //Initialize the sunpoints label
    sunPointsLbl->setText("Sun Points: 500");


}
//Add sun points when the user clicks a sun.
void mainGame::addSunPoints()
{
    //Add 25 sun points.
    sunPoints += 25;
    //Change the text of the sunPointsLbl.
    sunPointsLbl->setText(QString("Sun Points: %1").arg(sunPoints));
    //Check which plants can now be planted with the new sun points.
    this->checkPlants();
}
//removes sun points after a user clicks a sun.
void mainGame::removeSunPoints(int rPoints)
{
    //remove the cost of the plant just planted.
    sunPoints -= rPoints;
    //check which plants can now be planted with the new sun points.
    this->checkPlants();
    //No plant is selected.
    isPlantSelected = false;
    //Reset the cursor.
    QWidget::setCursor(Qt::ArrowCursor);
    //Change the text of the sunpointslbl
    sunPointsLbl->setText(QString("Sun Points: %1").arg(sunPoints));

}
//Return the plant the user wants to make.
Plant *mainGame::getPlant()
{
    return pObj;
}

void mainGame::checkPlants()
{

    //Enable all plants that cost 50
    if(sunPoints >= 50){
        sunFlowerBtn->setEnabled(true);
    }else{
        //Else set them all to false
        sunFlowerBtn->setEnabled(false);
    }
    //Enable all plants that cost at least 100
    if(sunPoints >= 100){
        peaShooterBtn->setEnabled(true);
    }else{
        //Else set them all to false.
        peaShooterBtn->setEnabled(false);
    }
}

mainGame::~mainGame()
{
    delete ui;
}

int mainGame::random(int x1, int x2)
{

}

void mainGame::on_sunflowerBtn_clicked()
{
    isPlantSelected = true;
    //Add the new sunflower to the plants vector.
    pObj = new Sunflower(mV); // Create the new sunFlower.
    //Sets up the cursor for the new plant.
    const QPixmap tempPix(":/Sunflower/Sunflower.gif"); // Get the sunflower image.
    tempPix.scaled(W,W); // Scale the image to desired size
    //Set the cursor to the plant.
    const QCursor tempCurs(tempPix);
    QWidget::setCursor(tempCurs);
}

void mainGame::keyPressEvent(QKeyEvent *mouseEvent)
{
    switch(mouseEvent->key()){
        case Qt::Key_Escape:
            if(isPlantSelected){
                delete pObj;
                //Reset the cursor
                QWidget::setCursor(Qt::ArrowCursor);
                //sets the plant selected to false.
                isPlantSelected = false;
                break;
            }
    }
}


//When the peashooter button is clicked, a peashooter icon will be prepped to be planted.
void mainGame::on_peashooterBtn_clicked()
{
    isPlantSelected = true;
    pObj = new Peashooter(mV); // Create the new peaShooter.
    //Sets up the cursor for the new plant.
    const QPixmap tempPix(":/Plants/PeaShooter.gif");
    tempPix.scaled(W,W); // Scale the image to desired size
    //Set the cursor to the plant.
    const QCursor tempCurs(tempPix);
    QWidget::setCursor(tempCurs);

}
