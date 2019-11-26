#include "BasicPlatform.h"
#include <QApplication>
#include <QDebug>

BasicPlatform::BasicPlatform() : Platform("basicPlatform.png") {

}

BasicPlatform::BasicPlatform(float yMin, float yMax) : Platform("basicPlatform.png", yMin, yMax){

}