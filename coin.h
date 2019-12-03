//
// Created by Yoann on 03/12/2019.
//

#ifndef DOODLEJUMP_COIN_H
#define DOODLEJUMP_COIN_H

#include "Platform.h"
#include "Bonus.h"

class Coin : public Bonus {
public:
    Coin(Platform* p);
};
#endif //DOODLEJUMP_COIN_H
