#ifndef DEFENCE_H
#define DEFENCE_H
#include <plant.h>
class Defence : public Plant
{
public:
    Defence();

protected:
    int splash;
    bool bomb;
    bool sun;
    bool need;



    // Plant interface
public:
    QString getImagePath();
};

#endif // DEFENCE_H
