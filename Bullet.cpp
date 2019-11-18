//
// Created by yoann on 21/10/2019.
//

#include "Bullet.h"
#include "consts.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>


Bullet::Bullet() {

    setPixmap(QPixmap(":/images/bullet.png"));

    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(move()));

    m_timer->start(BULLET_SPEED);
}

void Bullet::move(){
    setPos(x(),y()-3);
    if(pos().y()+pixmap().height() < 0){
        scene()->removeItem(this);
        m_timer->stop();
        delete this;
    }
}

Bullet::~Bullet() {
    delete m_timer;
};
