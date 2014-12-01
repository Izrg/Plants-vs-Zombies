#include "ref.h"
#include <QDebug>
Sun::Sun(int H)
{
    gametype = 'S';
    name = "Sun";

    gameBoardHeight = H;

    //Load sun image, and make it WxW
    setPixmap(QPixmap(":/sun/Sun.png").scaled(W,W));
}

void Sun::onCreate(bool falling, int endingRow)
{
    instances->back()->setData(isFalling, falling);
    //qDebug() << falling << endl;
    instances->back()->setData(endRow, endingRow);
    //qDebug() << endingRow << endl;

}
void Sun::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}

void Sun::advance(int phase)
{
    if(!phase) return;

    for(int i = 0; i < instances->size(); i++)
    {
        //Is the sun not falling?
        //qDebug() << instances->at(i)->data(isFalling).toBool() << " : " << instances->at(i)->data(endRow).toInt() << " ;; " << instances->at(i)->pos().y() << endl;
        if(!(instances->at(i)->data(isFalling)).toBool()){
            continue;
        }
        else if(instances->at(i)->pos().y() >= instances->at(i)->data(endRow).toInt() * gameBoardHeight + gameBoardHeight/4){
            instances->at(i)->setData(isFalling, false);
        }
        else {
            instances->at(i)->setY(instances->at(i)->pos().y() + 5);
        }
    }
}

