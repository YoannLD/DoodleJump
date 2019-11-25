#include "Monster.h"
#include <qDebug>

Monster::Monster(BasicPlatform* platform) {
    auto* monsterPixmap = new QPixmap();
    bool monsterLoaded = monsterPixmap->load(":/images/monster.png");
    if(!monsterLoaded) {
        qDebug() << "Error loading : :/images/monster.png";
    }
    setPixmap(*monsterPixmap);
    delete monsterPixmap;
    setPos(platform->x() + platform->pixmap().width()/2 - pixmap().width()/2, platform->y() - pixmap().height());

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
}

void Monster::kill() {
    setY(y()+1);
}

Monster::~Monster() {
    delete killTimer;
    delete jumpSound ;
    delete dieSound ;
}
