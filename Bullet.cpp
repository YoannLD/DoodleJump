#include "Bullet.h"
#include "consts.h"
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
}
