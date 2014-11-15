using namespace std;
#include "maingame.h"
#include "ui_maingame.h"
#include <mainwindow.h>
#include <qdebug.h>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <vector>
#include <sun.h>
#include <QtGlobal>
#include <QTime>
#include <QDebug>

vector <Sun*> suns;
vector <Sun*>::iterator sunIter;
static int sunIndex = 0;

mainGame::mainGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    moveTimer = new QTimer(this);
    //Set up grass textures.
    grass1.load(":/grass1/darkGrass.PNG");
    grass2.load(":/grass2/lightGrass.PNG");

    WIDTH = ui->gameBoard->width() -10;
    HEIGHT = ui->gameBoard->height() - 5;
    qDebug() << "WIDTH: " << WIDTH << "HEIGHT: " << HEIGHT << endl;
    scene = new QGraphicsScene(this);
    ui->gameBoard->setScene(scene);

    QGraphicsPixmapItem *item;

    //Set the size of hte screen.
    QRectF rect(0,0,WIDTH,HEIGHT);
    scene->setSceneRect(rect);

    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;
    QPen myPen = QPen(Qt::red);

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

    //Add new sun and add it to the scene.
    suns.push_back(new Sun(((this->random(0,ROWS-1))*gameBlockHeight +(gameBlockHeight/4)),(this->random(0,COLUMNS-1)*gameBlockWidth + (gameBlockWidth/4))));

    sunIter = suns.begin() + sunIndex;
    sunIndex ++;
    scene->addItem(*sunIter);

    connect(moveTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    moveTimer->start(100);

}

//Return a random number
int mainGame::random(int x1, int x2)
{
    return qrand() % ((x2 + 1) - x1) + x1;
}


int mainGame::getBlockHeight()
{
    return gameBlockHeight;
}


mainGame::~mainGame()
{
    delete ui;
}

void mainGame::on_sunflowerBtn_clicked()
{
//    mW = new MainWindow();
//    mW->show();
//    this->close();

}

