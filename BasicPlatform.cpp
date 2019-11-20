#include "BasicPlatform.h"
#include <QApplication>
#include <QDebug>

BasicPlatform::BasicPlatform() : Platform(":/images/basicPlatform.png") {

}

BasicPlatform::BasicPlatform(float yMin, float yMax) : Platform(":/images/basicPlatform.png", yMin, yMax){

}