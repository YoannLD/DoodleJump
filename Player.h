#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QList>
#include <QTimer>

class Player : public QObject, public Moving {
Q_OBJECT
public:
    Player();

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
    bool m_facingLeft = true;
    bool m_hasShot = false;
    int m_currentJumpHeight = 0;
    bool m_isFalling = false;
    QTimer* m_shootingPixmapTimer;
    QPixmap m_pixmap;
    QPixmap m_shootingPixmap;
    std::vector<int> m_events;
public slots:

    void move();
    void updatePixmap();


};

#endif //DOODLEJUMP_PLAYER_H
