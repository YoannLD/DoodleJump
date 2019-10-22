#include "Player.h"
#include "Bullet.h"
#include "consts.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>


void Player::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q){
        if(pos().x()+(pixmap().width()/2) > 0)
            setPos(x()-15,y());
        else
            setPos(scene()->width()-(pixmap().width()/2),y());
    }
    else if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        if(pos().x()+(pixmap().width()/2) < scene()->width())
            setPos(x()+15,y());
        else
            setPos(-pixmap().width()/2,y());
    }
    else if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Up || event->key() == Qt::Key_Z){
        auto * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }

}


void Player::updatePosition(float deltaTime) {
    /**setHorizontalPosition(MOVE_SPEED,deltaTime);
    updateTimeAccumulators(deltaTime);
    sf::Vector2f nextPosition = {pos().x(),getNextY()};
    setFallingState(nextPosition.y);
    setPos(nextPosition);*/
}

void Player::setHorizontalPosition(float nextX, float deltaTime) {

}

void Player::setFallingState(float nextY) {

}

float Player::getNextY() const {
    return 0;
}

void Player::setNextY(float nextY) {

}

void Player::resetTimeAccumulators() {

}

void Player::updateTimeAccumulators(float deltaTime) {

}


