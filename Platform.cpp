#include "Platform.h"
#include <QApplication>
#include <QDebug>
#include "consts.h"

float Platform::multiplier = WINDOW_HEIGHT;

Platform::Platform(const QString& path) {
    pixmap = new QPixmap();
    bool loaded = pixmap->load(path);
    if(!loaded) {
        qDebug() << "Error loading :" << path;
    }
    setPixmap(*pixmap);

    const float minX = pixmap->width() / 2;
    const float maxX = WINDOW_WIDTH - pixmap->width() ;
    setX(minX + (rand()% static_cast<int>(maxX-minX+1)));

    const float minY = -WINDOW_HEIGHT;
    const float maxY = Platform::multiplier;
    setY(minY+ (rand() % static_cast<int>(maxY-minY+1)));

}

Platform::Platform(const QString& path, float yMin, float yMax) : Platform(path){

    pixmap = new QPixmap();
    bool loaded = pixmap->load(path);
    if(!loaded) {
        qDebug() << "Error loading :" << path;
    }
    setPixmap(*pixmap);

    const float minX = pixmap->width() / 2;
    const float maxX = WINDOW_WIDTH - pixmap->width() ;
    setX(minX + (rand()% static_cast<int>(maxX-minX+1)));

    const float minY = yMin+yMin*15/100;
    const float maxY = yMax-yMax*15/100;
    setY(minY+ (rand() % static_cast<int>(maxY-minY+1)));


}

