//
// Created by yoann on 21/10/2019.
//

#include "Bullet.h"
#include <QTimer>
#include <QDebug>


Bullet::Bullet() {
    setPixmap(QPixmap("images/bullet.png"));
    move();

    auto * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(Bullet::move()));

    timer->start(50);
}

void Bullet::move(){
    qDebug() << "test";
    setPos(x(),y()-10);
}
