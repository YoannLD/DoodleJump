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

    nb_platform = 18;

    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    QPixmap backgroundPixmap = QPixmap();
    bool backgroundLoaded = backgroundPixmap.load(":/images/background.png");
    if(!backgroundLoaded) {
        qDebug() << "Error loading : :/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(backgroundPixmap));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);


    // create a player
    auto * player = new Player(this);

    player->setPos(scene->width()/2,scene->height()-player->pixmap().height()-10);


    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);

    text = scene->addText(QString::number(m_score),QFont("Al Seana"));
    text->setPos(10, 10);

    // create a platform
    addPlatform();

}

void Game::addPlatform() {

    int nb_actual_platform = 0;
    int platform_y_min = WINDOW_HEIGHT;
    for(auto element : scene->items()) {
        if(Platform* platform = dynamic_cast<Platform*>(element)){
            nb_actual_platform++;
            if(element->y() < platform_y_min){
                platform_y_min = element->y();
            }
        }
    }



    for(int i=0; i < nb_platform-nb_actual_platform; i++){
        BasicPlatform* platform = new BasicPlatform();

        platform = new BasicPlatform();

        if(scene->collidingItems(platform).size() == 0){

            //platform->setY(platform->y()-30);
            scene->addItem(platform);
        }

        else
            i--;
    }


}

void Game::increaseScore() {
    m_score++;
    text->setPlainText(QString::number(m_score));
}
