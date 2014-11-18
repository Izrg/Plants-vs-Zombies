using namespace std;
#include "maingame.h"
#include "ui_maingame.h"
#include <mainwindow.h>
#include <myview.h>
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
#include <QMouseEvent>
#include <QGraphicsView>


QGraphicsView *gB;

mainGame::mainGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainGame)
{
    ui->setupUi(this);
    mV = new myView(ui->gameBoard);

    sunPoints = 50;
    //Set up the timers
    moveTimer = new QTimer(this);
    sunTimer = new QTimer(this);
    //Set up grass textures.

    //Start the move timer to control movement.
    connect(moveTimer, SIGNAL(timeout()), mV->scene, SLOT(advance()));
    //Start the sun timer, which controls when suns spawn.
    connect(sunTimer, SIGNAL(timeout()), mV, SLOT(sunSpawn()));

    sunTimer->start(10000);
    moveTimer->start(100);


}


int mainGame::getBlockHeight()
{
    //return gameBlockHeight;
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

//void mainGame::mousePressEvent(QMouseEvent *event)
//{

    //QGraphicsItem *qG;
    //qG->mousePressEvent(event);      // call base class function to allow further processing
    //QGraphicsView::mousePressEvent(event);
    //mV = new myView(scene);
    //this->parent()) ui->gameBoard->scene->mapToScene(event->pos());
    //qDebug() << "TEST" << endl;
    //QGraphicsView tempView;
    //event.
    //QPointF testPoint = gB->mapToScene(event->pos());
    //qDebug() << "X: " << testPoint.x() << "Y: " << testPoint.y() << endl;
    //QGraphicsItem *tempItem = mainGame::scene->itemAt((qreal)event->x(),(qreal)event->y(),QTransform::scale());
    //qDebug() <<  << endl;
    //if(event->pos() == mainGame::scene->itemAt())
//}


