#include "Bullet.h"
#include "consts.h"
#include "Monster.h"
#include "Resources.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet(QTimer* timer) {
    setPixmap(Resources::png("bullet.png"));
    setZValue(149);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

void Bullet::move(){
    setY(y()-3);
}
