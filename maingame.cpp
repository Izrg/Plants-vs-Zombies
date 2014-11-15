#include "maingame.h"
#include "ui_maingame.h"
#include <qdebug.h>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QPainter>
#include <QGraphicsPixmapItem>

mainGame::mainGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);

    //Set up grass textures.
    grass1.load(":/grass1/darkGrass.PNG");
    grass2.load(":/grass2/lightGrass.PNG");

    WIDTH = ui->gameBoard->width() -10;
    HEIGHT = ui->gameBoard->height() - 5;

    scene = new QGraphicsScene(this);
    ui->gameBoard->setScene(scene);

    QGraphicsPixmapItem *item;

    QRectF rect(0,0,WIDTH,HEIGHT);
    scene->setSceneRect(rect);

    gameBlockHeight = HEIGHT/ROWS;
    gameBlockWidth = WIDTH/COLUMNS;
    QPen myPen = QPen(Qt::red);

    int widthStep = 0;
    int heightStep = 0;
    bool dark = true;
    //This loop is used to draw the grid.
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

}


mainGame::~mainGame()
{
    delete ui;
}

void mainGame::on_sunflowerBtn_clicked()
{

}
