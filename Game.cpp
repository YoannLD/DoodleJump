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
#include "BreakingPlatform.h"
#include "MovingPlatform.h"

Game::Game() {

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

    //player->setPos(scene->width()/2,scene->height()-player->pixmap().height()-10);
    player->setPos(scene->width()/2,0);


    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(100);

    scene->addItem(player);

    text = scene->addText(QString::number(m_score),QFont("Al Seana"));
    text->setPos(10, 10);

    // create a platform
    addPlatform();

}

void Game::calculateNumberOfPlatform(){
    // TODO : faire une énum 1000, 2500 et >= 2500
    if(m_score < 500){
        nb_platform_allow = nb_platform;
    }
    else if(m_score < 1000 ){
        nb_platform_allow = 30;
    }
    else
        nb_platform_allow = 20;
}


void Game::addPlatform() {

    int nb_actual_platform = 0;

    calculateNumberOfPlatform();

    for(auto element : scene->items()) {
        if(auto* platform = dynamic_cast<Platform*>(element)){
            nb_actual_platform++;
        }
    }

    if(nb_actual_platform < nb_platform_allow) {
        int i = 0;
        while (i < nb_platform_allow - nb_actual_platform) {
            int breaking = rand()% static_cast<int>(6+1);
            int moving = rand()% static_cast<int>(6+1);
            Platform *platform;
            if(breaking == 1)
                platform = new BreakingPlatform();
            else if(moving == 1)
                platform = new MovingPlatform();
            else
                platform = new BasicPlatform();

            if (scene->collidingItems(platform).empty()) {
                scene->addItem(platform);
                i++;
            }
        }

        QList<QGraphicsItem *> platforms;

        for(auto element : scene->items()) {
            if(auto* platform = dynamic_cast<BasicPlatform*>(element)){
                platforms.append(platform);
            }
        }

        if(!platforms.empty()) {
            quickSort(platforms, 0, platforms.size() - 1);
        }

        int j = 0;
        while(j < platforms.size()-1){
            float dist = QLineF(0, platforms.at(j)->y(), 0, platforms.at(j+1)->y()).length();
            if(dist > 150){
                auto* platform = new BasicPlatform(platforms.at(j)->y(), platforms.at(j + 1)->y());
                if(scene->collidingItems(platform).empty()){
                    scene->addItem(platform);
                }
            }
            j++;
        }

    }



}

void Game::increaseScore() {
    m_score++;
    text->setPlainText(QString::number(m_score));
}

void Game::quickSort(QList<QGraphicsItem *> &items, int low, int high){

    int i = low;
    int j = high;
    double pivot = items.at((i+j)/2)->y()+1000;

    while (i <= j)
    {
        while (items.at(i)->y()+1000 < pivot) {
            i++;
        }
        while (items.at(j)->y()+1000 > pivot) {
            j--;
        }
        if (i <= j)
        {
            items.swapItemsAt(i,j);
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(items, low, j);
    if (i < high)
        quickSort(items, i, high);

}
