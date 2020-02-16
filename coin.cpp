#include "coin.h"
#include "Resources.h"
#include <QDebug>

Coin::Coin(Platform* platform) : Bonus(platform){
    setPixmap(Resources::png("coin/coin0.png"));
    setPos(getPlatform()->x() + getPlatform()->pixmap().width()/2. - pixmap().width()/2., getPlatform()->y() - pixmap().height());
    setZValue(99);
    animationTimer = new QTimer();
    connect(animationTimer, &QTimer::timeout, this, &Coin::animation);
    animationTimer->start(50);
}

Coin::~Coin() {
    delete animationTimer;

}

void Coin::animation() {
    animation_state += 1;
    setPixmap(Resources::png("coin/coin" + QString::number(animation_state % 8) + ".png"));

}
