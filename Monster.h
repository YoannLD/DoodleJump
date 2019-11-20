#ifndef DOODLEJUMP_MONSTER_H
#define DOODLEJUMP_MONSTER_H

#include "Hurts.h"
#include "Moving.h"
#include "BasicPlatform.h"

class Monster : public Hurts {
public:
    Monster(BasicPlatform* p);
};

#endif //DOODLEJUMP_MONSTER_H
