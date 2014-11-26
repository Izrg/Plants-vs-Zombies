#pragma once
#ifndef MAINGAME_H
#define MAINGAME_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QSignalMapper>
#include <QToolButton>
#include <QList>
#include <QKeyEvent>

#include "mainwindow.h"
#include "myview.h"
#include "ref.h"

namespace Ui {
class mainGame;
}
class MainWindow;
class myView;
class Plant;
class mainGame : public QMainWindow
{
    Q_OBJECT

public:

    explicit mainGame(QWidget *parent = 0);
    enum {W = 50}; // Used for the size of the plant pictures.
    Ui::mainGame *ui;

    //List for Plant Parent Classes
    QList <Plant*> *plantObj;

    //List for Buttons
    QList <QToolButton*> *buttons;

    //integer value to reference plant selection ; -1 if NULL.
    int  plantSelected;

    //Sun Points
    int SunPoints;

    myView *mV; // delcare the myView object.
    void addSunPoints(); // Called to add sunpoints when a sun is clicked.
    void removeSunPoints(int rPoints); // Called to reset the cursor/subtrack the plants cost after a plant was planted.
    void checkPlants();
    ~mainGame();
    MainWindow *mW;
    bool plantsAdded;
    QSignalMapper* mapper; //For mapping signals -> Allows passing of values to SLOTs

public slots:
    void onPlantButtonClicked(int);

protected:
    void keyPressEvent(QKeyEvent *mouseEvent);
};

#endif // MAINGAME_H
