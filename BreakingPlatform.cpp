#include "BreakingPlatform.h"
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QMediaPlayer>

BreakingPlatform::BreakingPlatform() : Platform(":/images/breakingPlatform/breakingPlatform_1.png") {

    breakSound = new QMediaPlayer();
    breakSound->setMedia(QUrl("qrc:/sounds/break.mp3"));
    breakingTimer = new QTimer();
    connect(breakingTimer, &QTimer::timeout, this, &BreakingPlatform::breaking);

}

void BreakingPlatform::launchBreak(){
    breakingTimer->start(5);

    // Si le son est déjà lancé, remet à 0
    if (breakSound->state() == QMediaPlayer::PlayingState) {
        breakSound->setPosition(0);
    } else if (breakSound->state() == QMediaPlayer::StoppedState) {
        breakSound->play();
    }
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
