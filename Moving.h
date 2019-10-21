#ifndef DOODLEJUMP_MOVING_H
#define DOODLEJUMP_MOVING_H

#include "GameObject.h"

class Moving : public GameObject {
public slots:
    virtual void move() = 0;
};

#endif //DOODLEJUMP_MOVING_H
