#include "BreakingPlatform.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

BreakingPlatform::BreakingPlatform() : Platform(":/images/breakingPlatform/breakingPlatform_1.png") {


    breakingTimer = new QTimer();
    connect(breakingTimer, &QTimer::timeout, this, &BreakingPlatform::breaking);

}

void BreakingPlatform::launchBreak(){
    breakingTimer->start(5);
}

void BreakingPlatform::breaking(){
    if(state == 4){
        setY(y()+1);
    }
    else{

        state++;
        setPixmap(":/images/breakingPlatform/breakingPlatform_"+QString::number(state)+".png");
    }
}
