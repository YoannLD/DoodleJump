#include "Monster.h"
#include <qDebug>

Monster::Monster(BasicPlatform* platform) {
    auto* pixmap = new QPixmap();
    bool bulletLoaded = pixmap->load(":/images/loicMonster.png");
    if(!bulletLoaded) {
        qDebug() << "Error loading : :/images/loicMonster.png";
    }
    setPixmap(*pixmap);
    delete pixmap;
    setPos(platform->x(), platform->y() - pixmap->height());
}
