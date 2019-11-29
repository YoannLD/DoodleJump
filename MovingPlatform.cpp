#include "MovingPlatform.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <random>
#include "consts.h"
#include "Bonus.h"
#include "Monster.h"

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
            for(auto* element : associatedItems) {
                element->setX(element->x()-1);
            }
        }
        else{
            Platform::setX(Platform::x()+1);
            state = direction ::RIGHT;
            for(auto* element : associatedItems) {
                element->setX(element->x()+1);
            }
        }
    }
    else if(state == direction::RIGHT){
        if(Platform::x()+Platform::pixmap().width() < WINDOW_WIDTH-BORDER_LAYOUT){
            Platform::setX(Platform::x()+1);
            for(auto* element : associatedItems) {
                element->setX(element->x()+1);
            }
        }
        else{
            Platform::setX(Platform::x()-1);
            state = direction ::LEFT;
            for(auto* element : associatedItems) {
                element->setX(element->x()-1);
            }
        }
    }

}

MovingPlatform::~MovingPlatform() {
    delete movingTimer;
}

void MovingPlatform::addAssociatedItem(GameObject* item) {
    associatedItems.append(item);
}
