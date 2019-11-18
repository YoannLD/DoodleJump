#include "BasicPlatform.h"
#include <QApplication>
#include <QDebug>
#include "consts.h"

BasicPlatform::BasicPlatform() {
    // --------- Loading pixmaps ---------
    auto* pixmap = new QPixmap();
    bool loaded = pixmap->load(":/images/basicPlatform.png");
    if(!loaded) {
        qDebug() << "Error loading : :/images/basicPlatform.png";
    }
    setPixmap(*pixmap);

    const float minX = pixmap->width() / 2;
    const float maxX = WINDOW_WIDTH - pixmap->width() ;
    setX(minX + (rand()% static_cast<int>(maxX-minX+1)));

    const float minY = -200.f;
    const float maxY = Platform::multiplier;
    qDebug() << minY << maxY;
    setY(minY+ (rand() % static_cast<int>(maxY-minY+1)));

}
