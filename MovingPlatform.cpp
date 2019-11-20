#include "MovingPlatform.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "consts.h"

MovingPlatform::MovingPlatform() : Platform(":/images/movingPlatform.png") {

    // TODO : faire en sorte qu'il n'y ai pas de plateforme sur le trajet de celle ci
    movingTimer = new QTimer();
    connect(movingTimer, &QTimer::timeout, this, &MovingPlatform::move);
    movingTimer->start(15);

}

void MovingPlatform::move(){
    if(state == direction::LEFT){
        if(Platform::x() > 0){
            Platform::setX(Platform::x()-1);
        }
        else{
            Platform::setX(Platform::x()+1);
            state = direction ::RIGHT;
        }
    }
    else if(state == direction::RIGHT){
        if(Platform::x()+Platform::pixmap().width() < WINDOW_WIDTH){
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
