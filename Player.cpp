#include "Player.h"
#include "Bullet.h"
#include "consts.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QApplication>

Player::Player() {

    // --------- Loading pixmaps ---------
    m_pixmap = new QPixmap();
    bool doodleLoaded = m_pixmap->load(":/images/doodle.png");
    if(!doodleLoaded) {
        qDebug() << "Error loading : :/images/doodle.png";
    }

    m_shootingPixmap = new QPixmap();
    bool shootingLoaded = m_shootingPixmap->load(":/images/doodleShoot.png");
    if(!shootingLoaded) {
        qDebug() << "Error loading : :/images/doodleShoot.png";
    }
    setPixmap(*m_pixmap);

    // --------- Creating timers ---------
    m_shootTimer = new QTimer();
    m_shootingPixmapTimer = new QTimer();
    connect(m_shootingPixmapTimer,SIGNAL(timeout()),this,SLOT(updatePixmap()));
    m_shootTimer->start(BULLET_SPEED);
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
    setPixmap(*m_pixmap);
    if(!m_facingLeft) {
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
    }
}

void Player::bounce(int newVel) {
    m_velocityY = newVel;
}

Player::~Player() {
    delete m_shootingPixmapTimer;
    delete m_shootTimer;
    delete m_shootingPixmap;
    delete m_pixmap;
}

float Player::getVelocityY() {
    return m_velocityY;
}

void Player::setVelocityY(float newVelocity) {
    m_velocityY = newVelocity;
}





