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

    std::vector<int> m_events;
    bool m_facingLeft = true;
    bool m_hasShot = false;
    QTimer *m_shootTimer;
    QTimer *m_shootingPixmapTimer;

    float getVelocityY();

    void setVelocityY(float newVelocity);

private:

    float m_velocityY = 0;

public slots:

    void bounce(int newVel);

    void updatePixmap();


};

#endif //DOODLEJUMP_PLAYER_H
