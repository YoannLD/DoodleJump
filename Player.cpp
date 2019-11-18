#include "Player.h"
#include "Bullet.h"
#include "BasicPlatform.h"
#include "consts.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QApplication>

Player::Player(Game* game) : m_game(game){

    // --------- Loading pixmaps ---------
    m_pixmap = QPixmap();
    bool doodleLoaded = m_pixmap.load(QApplication::applicationDirPath() + "/images/doodle.png");
    if(!doodleLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/doodle.png";
    }

    m_shootingPixmap = QPixmap();
    bool shootingLoaded = m_shootingPixmap.load(QApplication::applicationDirPath() + "/images/doodleShoot.png");
    if(!shootingLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/doodleShoot.png";
    }
    setPixmap(m_pixmap);

    // --------- Creating timers ---------
    auto * timer = new QTimer();
    m_jumpTimer = new QTimer();
    m_shootingPixmapTimer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(m_jumpTimer,SIGNAL(timeout()),this,SLOT(moveJump()));
    connect(m_shootingPixmapTimer,SIGNAL(timeout()),this,SLOT(updatePixmap()));

    timer->start(5);
    m_jumpTimer->start(10);
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
                if(!m_hasShot) {
                    m_hasShot = true;
                    auto *bullet = new Bullet();
                    bullet->setPos(x() + pixmap().width() / 2, y());
                    scene()->addItem(bullet);

                    setPixmap(m_shootingPixmap);
                    m_shootingPixmapTimer->start(300);
                }
                break;
        }
    }
}

void Player::moveJump() {

    m_velocityY += gravity;
    if (y() + pixmap().height()>= WINDOW_HEIGHT) { // (Perdu)
        setY(WINDOW_HEIGHT - pixmap().height());
    } else {
        if(y() < hauteurMax) { // Hauteur max, scroll
            if(abs(m_velocityY) > 0.21) m_game->increaseScore();
            setY(hauteurMax);
            for(auto element : scene()->items()) {
                auto* platform = dynamic_cast<BasicPlatform*>(element);
                if(platform) {
                    element->setY(element->y() - m_velocityY);
                    if (element->y() > WINDOW_HEIGHT) { // Si plateforme en dessous de l'écran
                        scene()->removeItem(element);
                    }
                }
            }
        }
        setY(y() + m_velocityY);
    }

    if (m_velocityY > 0) {
        // On vérifie si on touche une plateforme
        for(auto element : scene()->collidingItems(this)) {
            auto* platform = dynamic_cast<BasicPlatform*>(element);
            if(platform) {
                m_velocityY = -7;
                setY(platform->y()-pixmap().height());
            }
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

void Player::updatePixmap() {
    m_shootingPixmapTimer->stop();
    setPixmap(m_pixmap);
    if(!m_facingLeft) {
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
    }
}

Player::~Player() {
    delete m_shootingPixmapTimer;
    delete m_jumpTimer;
}





