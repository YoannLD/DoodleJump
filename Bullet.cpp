//
// Created by yoann on 21/10/2019.
//

#include "Bullet.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet() {

    setPixmap(QPixmap("images/bullet.png"));

    auto * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(5);
}

void Bullet::move(){
    setPos(x(),y()-2);
    if(pos().y()+pixmap().height() < 0){
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet deleted";
    }
}
