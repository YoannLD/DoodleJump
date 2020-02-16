#include "Platform.h"
#include <QApplication>
#include <QDebug>
#include <QScreen>
#include "consts.h"
#include "Resources.h"

Platform::Platform(const QString& path) {
    setPixmap(Resources::png(path));

    const float minX = pixmap().width() / 2 + BORDER_LAYOUT;
    const float maxX = WINDOW_WIDTH - BORDER_LAYOUT - pixmap().width() ;
    setX(minX + (rand()% static_cast<int>(maxX-minX+1)));

    const float minY = -WINDOW_HEIGHT;
    const float maxY = WINDOW_HEIGHT;
    setY(minY+ (rand() % static_cast<int>(maxY-minY+1)));
}

Platform::Platform(const QString& path, float yMin, float yMax) : Platform(path){
    setPixmap(Resources::png(path));


    const float minX = pixmap().width() / 2 + BORDER_LAYOUT ;
    const float maxX = WINDOW_WIDTH - BORDER_LAYOUT - pixmap().width() ;

    setX(minX + (rand()% static_cast<int>(maxX-minX+1)));

    //setY(frand_a_b(yMin,yMax));
    setY(yMin+ (rand() % static_cast<int>(yMax-yMin+1)));
}

double Platform::frand_a_b(float a, float b){
    return ( rand()/(double)RAND_MAX) * (b-a) + a;
}