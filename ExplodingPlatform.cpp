#include "ExplodingPlatform.h"
#include <QKeyEvent>
#include <QTimer>

ExplodingPlatform::ExplodingPlatform() : Platform(":/images/explodingPlatform/explodingPlatform_1.png") {

    explodingTimer = new QTimer();
    connect(explodingTimer, &QTimer::timeout, this, &ExplodingPlatform::exploding);
}

ExplodingPlatform::ExplodingPlatform(float yMin, float yMax): Platform(":/images/explodingPlatform/explodingPlatform_1.png", yMin, yMax){

    explodingTimer = new QTimer();
    connect(explodingTimer, &QTimer::timeout, this, &ExplodingPlatform::exploding);
}

void ExplodingPlatform::lauchExplosing(){
    explodingTimer->start(5);
}

void ExplodingPlatform::exploding() {
    if(state > 8){
        delete this;
    }
    else{
        state++;
        setPixmap(":/images/breakingPlatform/breakingPlatform_"+QString::number(state)+".png");
    }
}

ExplodingPlatform::~ExplodingPlatform() {
    delete explodingTimer;
};