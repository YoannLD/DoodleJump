#include "Player.h"
#include "Bullet.h"
#include "consts.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

Player::Player() {
    auto * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start((int) m_speed);
}

void Player::keyPressEvent(QKeyEvent *event) {
    if(!(event->isAutoRepeat())) {

        // If the key isn't already in the vector
        if (std::find(m_events.begin(), m_events.end(), event->key()) == m_events.end()) {

            m_events.push_back(event->key());
        }
    }
}


void Player::keyReleaseEvent(QKeyEvent *event) {

    if(!(event->isAutoRepeat())) {
        // Remove from the vector
        m_events.erase(std::remove(m_events.begin(), m_events.end(), event->key()), m_events.end());
    }
}

void Player::move() {
    for (int key : m_events) {
        switch(key) {
            case Qt::Key_Left :
            case Qt::Key_Q :
                if (pos().x() + (pixmap().width() / 2) > 0)
                    setPos(x() - 1, y());
                else
                    setPos(scene()->width() - (pixmap().width() / 2), y());

                if (!m_facingLeft) {
                    m_facingLeft = true;
                    setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
                }
                break;
            case Qt::Key_Right :
            case Qt::Key_D :
                if (pos().x() + (pixmap().width() / 2) < scene()->width()) {
                    setPos(x() + 1, y());
                }
                else {
                    setPos(-pixmap().width() / 2, y());
                }

                if (m_facingLeft) {
                    m_facingLeft = false;
                    setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
                }
                break;
            case Qt::Key_Space:
            case Qt::Key_Up:
            case Qt::Key_Z :
                auto *bullet = new Bullet();
                bullet->setPos(x() + pixmap().width() / 2, y());
                scene()->addItem(bullet);
                break;
        }
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





