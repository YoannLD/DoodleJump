#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"
#include "consts.h"
#include "Game.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

class Player : public QObject, public Moving {
Q_OBJECT
public:
    Player(Game* game);
    ~Player();

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void updatePosition(float deltaTime) override;

    void setHorizontalPosition(float nextX, float deltaTime);

    void setFallingState(float nextY);

    float getNextY() const;

    void setNextY(float nextY);

    void resetTimeAccumulators();

    void updateTimeAccumulators(float deltaTime);

private:
    Game* m_game;
    bool m_facingLeft = true;
    bool m_hasShot = false;
    int m_currentJumpHeight = 0;
    float m_velocityX = 0;
    int hauteurMax = 2*WINDOW_HEIGHT/3;
    float gravity = 0.1;
    float m_velocityY = 0;
    bool m_isFalling = false;
    QTimer* m_shootingPixmapTimer;
    QTimer* m_jumpTimer;
    QTimer* m_fallTimer;
    QPixmap m_pixmap;
    QPixmap m_shootingPixmap;
    std::vector<int> m_events;
    QMediaPlayer* bounceSound ;
    QMediaPlayer* shootSound ;
    QMediaPlayer* fallSound ;
public slots:

    void move();
    void moveJump();
    void updatePixmap();
    void fall();


};

#endif //DOODLEJUMP_PLAYER_H
