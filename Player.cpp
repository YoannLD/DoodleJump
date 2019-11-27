#include "Player.h"
#include "Bullet.h"
#include "consts.h"
#include "Resources.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QApplication>

Player::Player() {
    setPixmap(Resources::png("doodle.png"));

    // --------- Creating timers ---------
    m_shootTimer = new QTimer();
    m_shootingPixmapTimer = new QTimer();
    connect(m_shootingPixmapTimer,SIGNAL(timeout()),this,SLOT(updatePixmap()));
    m_shootTimer->start(BULLET_SPEED);
    m_jetpack = false;
    jetpack = new QGraphicsPixmapItem();
    jetpack->setPixmap(Resources::png("jetpack/jetpack1.png"));
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
       if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Up || event->key() == Qt::Key_Z) {
           m_hasShot = false;
       }
    }
}


void Player::updatePixmap() {
    m_shootingPixmapTimer->stop();
    setPixmap(Resources::png("doodle.png"));
    if(!m_facingLeft) {
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
    }
}

void Player::bounce(float newVel) {
    m_velocityY = newVel;
}

Player::~Player() {
    delete m_shootingPixmapTimer;
    delete m_shootTimer;
    delete jetpack;
}

float Player::getVelocityY() {
    return m_velocityY;
}

void Player::setVelocityY(float newVelocity) {
    m_velocityY = newVelocity;
}

void Player::setJetpack() {
    if(m_facingLeft) {
        jetpack->setPos(x() + pixmap().width() - JETPACK_LAYOUT - DOODLE_LAYOUT, y() + DOODLE_LAYOUT);
    }
    else {
        jetpack->setPos(x() - jetpack->pixmap().width() + JETPACK_LAYOUT + DOODLE_LAYOUT, y() + DOODLE_LAYOUT);
    }
    scene()->addItem(jetpack);
    m_jetpack = true;
}

void Player::removeJetpack() {
    scene()->removeItem(jetpack);
    m_jetpack = false;
}

void Player::moveLeft() {
    if (x() + (pixmap().width() / 2.) > BORDER_LAYOUT) {
        setX(x() - 1);
        if (isOnJetpack()) {
            jetpack->setX(jetpack->x() - 1);
        }
    }
    else {
        setX(scene()->width() - BORDER_LAYOUT - (pixmap().width() / 2.));
        if (isOnJetpack()) {
            jetpack->setX(scene()->width() - BORDER_LAYOUT + (pixmap().width() / 2.));
        }
    }

    if (!m_facingLeft) {
        m_facingLeft = true;
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
        if (isOnJetpack()) {
            jetpack->setX(x() + pixmap().width() - JETPACK_LAYOUT - DOODLE_LAYOUT);
            jetpack->setPixmap(jetpack->pixmap().transformed(QTransform().scale(-1, 1)));
        }
    }
}

void Player::moveRight() {
    if (x() + (pixmap().width() / 2.) < scene()->width()-BORDER_LAYOUT) {
        setX(x() + 1);
        if (isOnJetpack()) {
            jetpack->setX(jetpack->x() + 1);
        }
    }
    else {
        setX(-pixmap().width() / 2. + BORDER_LAYOUT);
        if (isOnJetpack()) {
            jetpack->setX(-pixmap().width()+ BORDER_LAYOUT);
        }
    }

    if (m_facingLeft) {
        m_facingLeft = false;
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
        if (isOnJetpack()) {
            jetpack->setX(x() - jetpack->pixmap().width() + JETPACK_LAYOUT + DOODLE_LAYOUT);
            jetpack->setPixmap(jetpack->pixmap().transformed(QTransform().scale(-1, 1)));
        }
    }
}

bool Player::isOnJetpack() {
    return m_jetpack;
}

void Player::moveVertical(int newY) {
    int oldY = y();
    setY(newY);
    if(isOnJetpack()) {
        jetpack->setY(jetpack->y() + newY-oldY);
    }
}





