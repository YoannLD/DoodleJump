#ifndef DOODLEJUMP_MOVINGPLATFORM_H
#define DOODLEJUMP_MOVINGPLATFORM_H

#include "Platform.h"
#include "Moving.h"

class MovingPlatform : public Platform, public Moving {
public:
    MovingPlatform();
private:
    QTimer * movingTimer;
    enum direction {LEFT, RIGHT};
    direction state = direction::LEFT;

public slots:
    void move();
};

#endif //DOODLEJUMP_MOVINGPLATFORM_H
