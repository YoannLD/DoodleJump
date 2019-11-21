#include "Monster.h"
#include <qDebug>

Monster::Monster(BasicPlatform* platform) {
    auto* monsterPixmap = new QPixmap();
    /*bool monsterLoaded = monsterPixmap->load(":/images/loicMonster.png");
    if(!monsterLoaded) {
        qDebug() << "Error loading : :/images/loicMonster.png";
    }
    setPixmap(*monsterPixmap);*/
    delete monsterPixmap;
    setPos(platform->x(), platform->y() - pixmap().height());
}
