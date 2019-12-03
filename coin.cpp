//
// Created by Yoann on 03/12/2019.
//

#include "coin.h"
#include "Resources.h"

Coin::Coin(Platform* platform) : Bonus(platform){
    setPixmap(Resources::png("coin/coin1.png"));
    setPos(getPlatform()->x() + getPlatform()->pixmap().width()/2. - pixmap().width()/2., getPlatform()->y() - pixmap().height());
    setZValue(99);
}