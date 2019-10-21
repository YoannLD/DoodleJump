#include "Player.h"
#include "Bullet.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>

void Player::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q){
        setPos(x()-15,y());
    }
    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        setPos(x()+15,y());
    }
    else if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Up || event->key() == Qt::Key_Z){
        Bullet * bullet = new Bullet();
        scene()->addItem(bullet);
    }
}
