#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include "consts.h"

class Player : public Moving{

public:
    void keyPressEvent(QKeyEvent * event) override;
    void updatePosition(float deltaTime) override;
private:
    bool m_isFalling = false;
    float m_speed = DOODLER_SPEED;

    void setHorizontalPosition(float nextX,float deltaTime);

    void setFallingState(float nextY);

    float getNextY() const;

    void setNextY(float nextY);

    void resetTimeAccumulators();

    void updateTimeAccumulators(float deltaTime);


};

#endif //DOODLEJUMP_PLAYER_H
