#include "ref.h"
extern QList<QList<QGraphicsPixmapItem*>*> *zombieGridList;
Bullet::Bullet(myView *rMV)
{
    gametype = 'B';
    name = "Bullet";

    speed = 7;

    mV = rMV;
    //Load sun image, and make it WxW
    setPixmap(QPixmap(":/Plants/Bullet.PNG").scaled(W,W));
    snowBullet = new QPixmap(":/Plants/SnowBullet.png");
    *snowBullet = snowBullet->scaled(W,W);

}

void Bullet::advance(int phase)
{
    if(!phase) return;

    //Handle collisions of Bullets with Zombie-scum
    for(int i =0; i < instances->size(); i++)
    {
        if(!zombieGridList->at(instances->at(i)->data(ROW_INDEX).toInt())->isEmpty())
        {
            //For each of the zombies in the bullets row...
            for(int j = 0; j < zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->size(); j++)
            {
                //If the bullet hits one of them
                //CRASHES HERE AFTER A ZOMBIE THAT SPAWNED AFTER ANOTHER ONE DIES FIRST.
                if(zombieGridList->at(instances->at(i)->data(ROW_INDEX).toInt())->at(j)->data(INSTANCE_LIFE).toInt() <= 0)
                {
                    //qDebug() << "Inctances at i: " << instances->at(i)->data(ROW_INDEX).toInt() << endl;
                    //qDebug() << "mV->zombigridLis size: " << zombieGridList->at(instances->at(i)->data(ROW_INDEX).toInt())->size() << endl;
                    //qDebug() << "Zombie gtidlist at j row: " << zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(ROW_INDEX).toInt() << endl;

                    continue;
                }

               if(instances->at(i)->collidesWithItem(zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)))
                {
                    //Save the plant Object and instance that shot this bullet.
                    int plantObject = instances->at(i)->data(PvZ::PLANT_TYPE).toInt();

                    int zombieInstance = zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::INSTANCE_INDEX).toInt();
                    mV->damageZombie(zombieGridList->at(instances->at(i)->data(PvZ::ROW_INDEX).toInt())->at(j)->data(PvZ::ZOMBIE_TYPE).toInt() , zombieInstance, j , instances->at(i)->data(PvZ::INSTANCE_DAMAGE).toInt(), mV->plantObj->at(plantObject)->slow);
                    //Delete the bullet.
                    delete instances->at(i);
                    instances->removeAt(i--);
                    break;
                }
            }
        }
    }

    //Move the bullets
    for(int i = 0; i < instances->size(); i++)
    {
        //Move the bullet across the screen at its speed
        instances->at(i)->setX(instances->at(i)->x() + speed);

        //If the bullet goes off the screen, destroy it.
        if(instances->at(i)->pos().x() + pixmap().width() >= mV->WIDTH){
            delete instances->at(i);
            instances->removeAt(i--);
            continue;
        }
    }
}


QPixmap *Bullet::getBullet(bool slow)
{
    QPixmap tempPix = pixmap();
    if(!slow) return &tempPix;
    return snowBullet;

}

void Bullet::destroy(int index)
{
    delete instances->at(index);
    instances->removeAt(index);
}
