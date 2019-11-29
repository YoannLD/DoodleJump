#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H

#include "GameObject.h"
#include "Platform.h"

class Bonus : public GameObject {
    public:
        Bonus(Platform* p);
        Platform* getPlatform();
    private:
        Platform* m_platform;
};

#endif //DOODLEJUMP_BONUS_H
