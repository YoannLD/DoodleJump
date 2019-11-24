#include "Bullet.h"
#include "consts.h"
#include "Monster.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet(QTimer* timer) {

    auto* bulletPixmap = new QPixmap();
    bool bulletLoaded = bulletPixmap->load(":/images/bullet2.png");
    if(!bulletLoaded) {
        qDebug() << "Error loading : :/images/bullet2.png";
    }
    setPixmap(*bulletPixmap);

    delete bulletPixmap;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void Bullet::move(){
    setY(y()-1);
    for(auto element : scene()->collidingItems(this)) {
        if (auto* monster = dynamic_cast<Monster*>(element)) { // Monstre
            monster->getShot();
            scene()->removeItem(monster);
            delete monster;
            delete this; // Sale mais si on veut faire mieux faut vérifier dans game, constamment, si une des balles touche un monstre
        }
    }
}
