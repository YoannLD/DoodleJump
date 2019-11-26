#include "Bullet.h"
#include "consts.h"
#include "Monster.h"
#include "Resources.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet(QTimer* timer) {
    setPixmap(Resources::png("bullet.png"));
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void Bullet::move(){
    setY(y()-1);
    for(auto element : scene()->collidingItems(this)) {
        if (auto* monster = dynamic_cast<Monster*>(element)) { // Monstre
            monster->getShot();
            //scene()->removeItem(monster);
            //delete monster; ( Laisse pas le temps de jouer le son)
            delete this; // Sale mais si on veut faire mieux faut vérifier dans game, constamment, si une des balles touche un monstre
        }
    }
}
