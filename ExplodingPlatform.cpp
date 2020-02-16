#include "ExplodingPlatform.h"
#include <QKeyEvent>
#include <QTimer>

ExplodingPlatform::ExplodingPlatform() : Platform("explodingPlatform/explodingPlatform_1.png") {
    explodingTimer = new QTimer();
    connect(explodingTimer, &QTimer::timeout, this, &ExplodingPlatform::exploding);
}

ExplodingPlatform::ExplodingPlatform(float yMin, float yMax): Platform("explodingPlatform/explodingPlatform_1.png", yMin, yMax){
    explodingTimer = new QTimer();
    connect(explodingTimer, &QTimer::timeout, this, &ExplodingPlatform::exploding);
}

void ExplodingPlatform::launchExplosing() {
    QTimer::singleShot(1000, this, &ExplodingPlatform::startTimer);
}

void ExplodingPlatform::startTimer(){
    explodingTimer->start(120);
}

void ExplodingPlatform::exploding() {
    if(state > 8)
        delete this;
    else{
        state++;
        setPixmap(":/images/explodingPlatform/explodingPlatform_"+QString::number(state)+".png");
    }
}

ExplodingPlatform::~ExplodingPlatform() {
    delete explodingTimer;
};