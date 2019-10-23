//
// Created by Benoît on 21/10/2019.
//

#include "Game.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>
#include "consts.h"

Game::Game() {
    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    QPixmap backgroundPixmap = QPixmap();
    bool backgroundLoaded = backgroundPixmap.load(QApplication::applicationDirPath() + "/images/background.png");
    if(!backgroundLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(backgroundPixmap));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);


    // create a player
    auto * player = new Player();

    player->setPos(scene->width()/2,scene->height()-player->pixmap().height());



    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);


}

