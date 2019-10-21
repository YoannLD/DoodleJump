//
// Created by yoann on 21/10/2019.
//

#include "Bullet.h"
#include <QTimer>
#include <QDebug>


Bullet::Bullet() {
    setPixmap(QPixmap("images/bullet.png"));
    //move();

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Bullet::move(){
    setPos(x(),y()-10);
}
