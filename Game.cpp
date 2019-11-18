//
// Created by Benoît on 21/10/2019.
//

#include "Game.h"
#include "Player.h"
#include "BasicPlatform.h"
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

    player->setPos(scene->width()/2,scene->height()-player->pixmap().height()-10);


    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);
    // create a platform
    for(int i=0; i < 18; i++){
        BasicPlatform* platform = new BasicPlatform();
        if(scene->collidingItems(platform).size() == 0)
            scene->addItem(platform);
        else
            i--;
    }


}

