#ifndef DOODLEJUMP_MOVING_H
#define DOODLEJUMP_MOVING_H

#include "GameObject.h"

class Moving : public GameObject {
public:
    virtual void updatePosition(float deltaTime){
        (void) &deltaTime;
    }
};

#endif //DOODLEJUMP_MOVING_H
