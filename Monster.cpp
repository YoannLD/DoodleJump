#include "Monster.h"
#include "Resources.h"
#include <qDebug>

Monster::Monster(BasicPlatform* platform) {
    setPixmap(Resources::png("monster.png"));
    setPos(platform->x() + platform->pixmap().width()/2 - pixmap().width()/2, platform->y() - pixmap().height());
    setZValue(120);

    jumpSound = new QMediaPlayer();
    dieSound = new QMediaPlayer();
    dieSound->setMedia(QUrl("qrc:/sounds/killMonster.mp3"));
    jumpSound->setMedia(QUrl("qrc:/sounds/jumpMonster.mp3"));
    killTimer = new QTimer();
    connect(killTimer, &QTimer::timeout, this, &Monster::kill);
}

void Monster::launchKill(){
    killTimer->start(2);
    // Si le son est déjà lancé, remet à 0
    if (jumpSound->state() == QMediaPlayer::PlayingState) {
        jumpSound->setPosition(0);
    } else if (jumpSound->state() == QMediaPlayer::StoppedState) {
        jumpSound->play();
    }
}

void Monster::getShot(){
    // Si le son est déjà lancé, remet à 0
    if (dieSound->state() == QMediaPlayer::PlayingState) {
        dieSound->setPosition(0);
    } else if (dieSound->state() == QMediaPlayer::StoppedState) {
        dieSound->play();
    }
    delete this; // Sale, à faore dans bullet ou game, mais sinon on peut pas jouer le son
}

void Monster::kill() {
    setY(y()+1);
}

Monster::~Monster() {
    delete killTimer;
    delete jumpSound ;
    delete dieSound ;
}
