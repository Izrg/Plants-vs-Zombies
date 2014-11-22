#ifndef REGULAR_H
#define REGULAR_H
#include <zombie.h>

class Regular : public Zombie
{
public:
    Regular(int row, int column);

    QPointF p;
    QPointF regularLocation;
    QPixmap regularPix;
    void setLocation(int column,int row);

    enum{W=50}; //size for the zombie pixmap
    void advance(int phase); //advance function for the zombie.
};

#endif // REGULAR_H
