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
};

#endif // DEFENCE_H
