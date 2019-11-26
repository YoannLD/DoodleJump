#ifndef DOODLEJUMP_MOVINGPLATFORM_H
#define DOODLEJUMP_MOVINGPLATFORM_H

#include "Platform.h"
#include "Moving.h"

class MovingPlatform : public Platform, public Moving {
public:
    MovingPlatform();

    MovingPlatform(float yMin, float yMax);

    ~MovingPlatform();
private:
    QTimer * movingTimer;
    enum direction {LEFT, RIGHT};
    direction state;

public slots:
    void move();
};

#endif //DOODLEJUMP_MOVINGPLATFORM_H
