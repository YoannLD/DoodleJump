//
// Created by Yoann on 24/11/2019.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"
#include "BasicPlatform.h"

class Spring : public Bonus {
public:
    Spring(BasicPlatform* p);
    void jump();
private:
    BasicPlatform* m_platform;
};
#endif //DOODLEJUMP_SPRING_H
