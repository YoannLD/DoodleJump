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
    m_jetpackUpdateTimer = new QTimer();
    m_jetpackFallTimer = new QTimer();
    m_shootingPixmapTimer = new QTimer();
    connect(m_shootingPixmapTimer,SIGNAL(timeout()),this,SLOT(updatePixmap()));
    connect(m_jetpackUpdateTimer,SIGNAL(timeout()),this,SLOT(updateJetpackPixmap()));
    connect(m_jetpackFallTimer,SIGNAL(timeout()),this,SLOT(jetpackFall()));
    m_shootTimer->start(BULLET_SPEED);
    m_jetpack = false;
    m_jetpackState = 0;
    m_jetpackCpt = 0;
    m_rotationJetpack = 0;
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
    delete m_jetpackUpdateTimer;
    delete m_jetpackFallTimer;
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
    if(!scene()->items().contains(jetpack)) {
        scene()->addItem(jetpack);
    }
    m_jetpack = true;
    m_jetpackState = 1;
    m_jetpackUpdateTimer->start(50);
}

void Player::removeJetpack() {
    m_jetpack = false;
    m_jetpackUpdateTimer->stop();
    jetpack->setPixmap(Resources::png("jetpack/jetpack10.png"));
    m_rotationJetpack = 0;
    m_jetpackFallTimer->start(2);
    m_jetpackState = 0;
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

void Player::updateJetpackPixmap() {
    switch(m_jetpackState) {
        case 0:
            if(m_jetpackCpt > 5) {
                m_jetpackState = 1;
            }
            else {
                if (jetpack->pixmap() == Resources::png("jetpack/jetpack1.png")) {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack2.png"));
                } else {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack1.png"));
                }
            }
            break;
        case 1:
            if(m_jetpackCpt > 10) {
                m_jetpackState = 2;
            }
            else {
                if (jetpack->pixmap() == Resources::png("jetpack/jetpack2.png")) {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack3.png"));
                } else {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack2.png"));
                }
            }
            break;
        case 2:
            if(m_jetpackCpt > 15) {
                m_jetpackState = 3;
            }
            else {
                if (jetpack->pixmap() == Resources::png("jetpack/jetpack4.png")) {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack5.png"));
                } else {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack4.png"));
                }
            }
            break;
        case 3:
            if(m_jetpackCpt > 40) {
                m_jetpackState = 4;
            }
            else {
                if (jetpack->pixmap() == Resources::png("jetpack/jetpack5.png")) {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack6.png"));
                } else {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack5.png"));
                }
            }
            break;
        case 4:
            if(m_jetpackCpt > 50) {
                m_jetpackState = 5;
            }
            else {
                if (jetpack->pixmap() == Resources::png("jetpack/jetpack7.png")) {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack8.png"));
                } else {
                    jetpack->setPixmap(Resources::png("jetpack/jetpack7.png"));
                }
            }
            break;
        case 5:
            if (jetpack->pixmap() == Resources::png("jetpack/jetpack9.png")) {
                jetpack->setPixmap(Resources::png("jetpack/jetpack10.png"));
            }
            else {
                jetpack->setPixmap(Resources::png("jetpack/jetpack9.png"));
            }
            break;
        default:
            qDebug() << "erreur";
            break;
    }
    if (!m_facingLeft) {
        jetpack->setPixmap(jetpack->pixmap().transformed(QTransform().scale(-1, 1)));
    }
    m_jetpackCpt++;
}

void Player::jetpackFall() {
    if(jetpack->y() <= WINDOW_HEIGHT) {
        jetpack->setY(jetpack->y() + 1);
        jetpack->setRotation(m_rotationJetpack);
        m_rotationJetpack += 0.2;
    }
    else {
        m_jetpackFallTimer->stop();
        m_rotationJetpack = 0;
        jetpack->setRotation(m_rotationJetpack);
        scene()->removeItem(jetpack);
    }
}





