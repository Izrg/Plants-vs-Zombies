#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include <defence.h>
#include <QMovie>
#include <sun.h>

class myView;
class Sunflower : public Defence
{
public:
    Sunflower();
    void makeSun();
    myView *mV;
    QTimer *sunflowerTimer;

    // Plant interface
public:
    QString getImagePath();
};

#endif // SUNFLOWER_H
