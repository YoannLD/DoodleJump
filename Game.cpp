//
// Created by Benoît on 21/10/2019.
//

#include "Game.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>

Game::Game() {
    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,600,900);

    QPixmap backgroundPixmap = QPixmap();
    bool backgroundLoaded = backgroundPixmap.load(QApplication::applicationDirPath() + "/images/background.png");
    if(!backgroundLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(backgroundPixmap));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,900);


    // create a player
    Player * player = new Player();
    QPixmap doodlePixmap = QPixmap();
    bool doodleLoaded = doodlePixmap.load(QApplication::applicationDirPath() + "/images/doodle.png");
    if(!doodleLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/doodle.png";
    }
    player->setPixmap(doodlePixmap);

    player->setPos(scene->width()/2,scene->height()-doodlePixmap.height());



    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);


}

