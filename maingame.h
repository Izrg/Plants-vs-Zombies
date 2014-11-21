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
    Ui::mainGame *ui;
    QPushButton testBtn;
    //initilize the vector for the plants.
    vector <Plant*> plants;
    vector <Plant*>::iterator plantsIter;
    //Bool to check if the user has selected a plant.
    bool isPlantSelected;

    myView *mV;
    int plantsIndex;
    void addSunPoints(); // Called to add sunpoints when a sun is clicked.
    void removeSunPoints(); // Called to reset the cursor/subtrack the plants cost after a plant was planted.
    void checkPlants();
    ~mainGame();
    MainWindow *mW;

private slots:
    void on_sunflowerBtn_clicked();


private:

    QTimer *moveTimer;
    QTimer *sunTimer;


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *mouseEvent);
};

#endif // MAINGAME_H
