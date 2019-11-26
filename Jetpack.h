//
// Created by yoann on 26/11/2019.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"
#include "BasicPlatform.h"

class Jetpack : public Bonus {
public:
    Jetpack(BasicPlatform* p);
private:
    BasicPlatform* m_platform;
};

#endif //DOODLEJUMP_JETPACK_H
