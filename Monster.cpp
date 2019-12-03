#include "Monster.h"
#include "Resources.h"
#include <qDebug>

Monster::Monster(Platform* platform) {
    setPixmap(Resources::png("monster_1.png"));
    setPos(platform->x() + platform->pixmap().width()/2 - pixmap().width()/2, platform->y() - pixmap().height());
    setZValue(120);
    animationTimer = new QTimer();
    killTimer = new QTimer();
    connect(animationTimer, &QTimer::timeout, this, &Monster::animation);
    connect(killTimer, &QTimer::timeout, this, &Monster::kill);

    animationTimer->start(250);
}

void Monster::launchKill(){
    killTimer->start(3);
}

void Monster::kill() {
    setY(y()+1);
}

void Monster::animation() {
    if(animation_state == 1){
        setPixmap(Resources::png("monster_2.png"));
        animation_state = 2;
    }
    else if(animation_state == 2){
        setPixmap(Resources::png("monster_1.png"));
        animation_state = 1;
    }

}

Monster::~Monster() {
    delete animationTimer;
    delete killTimer;
}
