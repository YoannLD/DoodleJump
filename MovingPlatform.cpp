#include "MovingPlatform.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <random>
#include "consts.h"

MovingPlatform::MovingPlatform() : Platform("movingPlatform.png") {

    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

    if(gen() != 0)
        state = direction ::RIGHT;
    else
        state = direction ::LEFT;

    movingTimer = new QTimer();
    connect(movingTimer, &QTimer::timeout, this, &MovingPlatform::move);
    movingTimer->start(15);

}

MovingPlatform::MovingPlatform(float yMin, float yMax) : Platform("movingPlatform.png", yMin, yMax){

    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());

    if(gen() != 0)
        state = direction ::RIGHT;
    else
        state = direction ::LEFT;

    movingTimer = new QTimer();
    connect(movingTimer, &QTimer::timeout, this, &MovingPlatform::move);
    movingTimer->start(15);
}

void MovingPlatform::move(){
    if(state == direction::LEFT){
        if(Platform::x() > BORDER_LAYOUT){
            Platform::setX(Platform::x()-1);
        }
        else{
            Platform::setX(Platform::x()+1);
            state = direction ::RIGHT;
        }
    }
    else if(state == direction::RIGHT){
        if(Platform::x()+Platform::pixmap().width() < WINDOW_WIDTH-BORDER_LAYOUT){
            Platform::setX(Platform::x()+1);
        }
        else{
            Platform::setX(Platform::x()-1);
            state = direction ::LEFT;
        }
    }
}

MovingPlatform::~MovingPlatform() {
    delete movingTimer;
}
