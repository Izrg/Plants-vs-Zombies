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
#include "fparcer.h"
#include "pausemenu.h"

namespace Ui {
class mainGame;
}
class MainWindow;
class myView;
class PauseMenu;
class Plant;
class mainGame : public QMainWindow
{
    Q_OBJECT

public:
    Fparcer* levelParce;
    //Stores the information read from the file.
    int startTime,interval,maxZombies;
    double decrement;
    QString name;
    QList<int> sequence;


    MainWindow* mW;
    PauseMenu* pM;
    int currentLevel;//Holds the current level.
    explicit mainGame(QWidget *parent = 0, MainWindow *rMW = 0);
    enum {W = 50}; // Used for the size of the plant pictures.
    Ui::mainGame *ui;

    //List for Plant Parent Classes
    QList <Plant*> *plantObj;

    //List for Buttons
    QList <QToolButton*> *buttons;

    //integer value to reference plant selection ; -1 if NULL.
    int  plantSelected;
    bool shovelLock;

    //Sun Points
    int SunPoints;

    int activeRow;

    myView *mV; // delcare the myView object.
    void addSunPoints(); // Called to add sunpoints when a sun is clicked.
    void removeSunPoints(int rPoints); // Called to reset the cursor/subtrack the plants cost after a plant was planted.
    void checkPlants();
    ~mainGame();
    bool plantsAdded;
    bool isPaused;
    QSignalMapper* mapper; //For mapping signals -> Allows passing of values to SLOTs
    void levelWon();
public slots:
    void onPlantButtonClicked(int);
    void on_shovelButton_clicked();
    void on_menuBtn_clicked();

protected:
    void keyPressEvent(QKeyEvent *mouseEvent);
private slots:

};

#endif // MAINGAME_H
