#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

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

    float m_velocityY = 0;
    std::vector<int> m_events;
    bool m_facingLeft = true;
    bool m_hasShot = false;
    QTimer* m_shootTimer;
    QPixmap* m_shootingPixmap;
    QTimer* m_shootingPixmapTimer;

private:
    QPixmap* m_pixmap;
    QMediaPlayer* bounceSound ;
public slots:

    void bounce();
    void move();
    void updatePixmap();


};

#endif //DOODLEJUMP_PLAYER_H
