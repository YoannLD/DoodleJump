#ifndef DOODLEJUMP_EXPLODINGPLATFORM_H
#define DOODLEJUMP_EXPLODINGPLATFORM_H

#include "Platform.h"


class ExplodingPlatform : public Platform {
public:
    ExplodingPlatform();
    ExplodingPlatform(float yMin, float yMax);
    void lauchExplosing();
    ~ExplodingPlatform();
private:
    QTimer* explodingTimer;
    int state = 1;


public slots:
    void exploding();
};

#endif //DOODLEJUMP_EXPLODINGPLATFORM_H
