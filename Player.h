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


};

#endif //DOODLEJUMP_PLAYER_H
