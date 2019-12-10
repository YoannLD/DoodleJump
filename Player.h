#ifndef CROCROJUMP_PLAYER_H
#define CROCROJUMP_PLAYER_H

#include "Moving.h"
#include "consts.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

class Player : public QObject, public Moving {
Q_OBJECT
public:
    Player();

    ~Player();

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    std::vector<int> m_events;
    bool m_facingLeft = true;
    bool m_hasShot = false;
    QTimer *m_shootTimer;
    QTimer *m_shootingPixmapTimer;
    QTimer *m_jetpackUpdateTimer;
    QTimer *m_jetpackFallTimer;

    float getVelocityY();

    void setVelocityY(float newVelocity);
    void setJetpack();
    void removeJetpack();
    void moveLeft();
    void moveRight();
    void moveVertical(int newY);
    bool isOnJetpack();
    void setFalling(bool f);
    bool isFacingLeft();
    bool isHit();
    void setHit(bool hit);
private:

    float m_velocityY = 0;
    QGraphicsPixmapItem* jetpack{};
    bool m_jetpack;
    int m_jetpackState;
    int m_jetpackCpt;
    float m_rotationJetpack;
    bool m_falling;
    bool m_isHit;

public slots:

    void bounce(float newVel);

    void updatePixmap();

    void updateJetpackPixmap();

    void jetpackFall();
};

#endif //CROCROJUMP_PLAYER_H
