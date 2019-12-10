#ifndef CROCROJUMP_MOVING_H
#define CROCROJUMP_MOVING_H

#include "GameObject.h"

class Moving : public GameObject {
public:
    virtual void updatePosition(float deltaTime){
        (void) &deltaTime;
    }
};

#endif //CROCROJUMP_MOVING_H
