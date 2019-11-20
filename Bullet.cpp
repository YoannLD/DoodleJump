#include "Bullet.h"
#include "consts.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet(QTimer* timer) {

    auto* pixmap = new QPixmap();
    bool bulletLoaded = pixmap->load(":/images/bullet2.png");
    if(!bulletLoaded) {
        qDebug() << "Error loading : :/images/bullet2.png";
    }
    setPixmap(*pixmap);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void Bullet::move(){
    setY(y()-1);
}
