#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject {

public:
    static void incrementMultiplier();
    static void resetMultiplier();

protected:
    static float multiplier;
};

#endif //DOODLEJUMP_PLATFORM_H
