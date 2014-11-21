using namespace std;
#ifndef MAINGAME_H
#define MAINGAME_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <Qpixmap>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <mainwindow.h>
#include <QWidget>
#include <vector>
#include <plant.h>
#include <QPushButton>

namespace Ui {
class mainGame;
}
class MainWindow;
class myView;

class mainGame : public QMainWindow
{
    Q_OBJECT

public:

    explicit mainGame(QWidget *parent = 0);
    enum {W= 50}; // Used for the size of the plant pictures.
    Ui::mainGame *ui;

    Plant *pObj;

    //Bool to check if the user has selected a plant.
    bool isPlantSelected;

    myView *mV; // delcare the myView object.
    void addSunPoints(); // Called to add sunpoints when a sun is clicked.
    void removeSunPoints(int rPoints); // Called to reset the cursor/subtrack the plants cost after a plant was planted.
    Plant *getPlant();
    void checkPlants();
    ~mainGame();
    MainWindow *mW;

private slots:
    void on_sunflowerBtn_clicked();


    void on_peashooterBtn_clicked();

private:

    QTimer *moveTimer;
    QTimer *sunTimer;



    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *mouseEvent);
};

#endif // MAINGAME_H
