#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"
#include "Platform.h"

class Spring : public Bonus {
public:
    Spring(Platform* p);
    void jump();
};
#endif //DOODLEJUMP_SPRING_H
