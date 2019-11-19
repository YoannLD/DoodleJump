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

int Game::getNbPlateformsAllow(){

}


void Game::addPlatform() {

    int nb_actual_platform = scene->items().size()-1;

    int i = 0;
    while(i< nb_platform-nb_actual_platform){
        auto* platform = new BasicPlatform();
        if(scene->collidingItems(platform).empty()){
            scene->addItem(platform);
            i++;
        }
    }

    QList<QGraphicsItem *> platforms;

    for(auto element : scene->items()) {
        if(auto* platform = dynamic_cast<Platform*>(element)){
            nb_actual_platform++;
            platforms.append(platform);
        }
    }

    if(!platforms.empty()) {
        quickSort(platforms, 0, platforms.size() - 1);
    }

    int j = 0;
    while(j < platforms.size()-1){
        float dist = QLineF(0, platforms.at(j)->y(), 0, platforms.at(j+1)->y()).length();
        if(dist > 100){
            qDebug() << dist;
            auto* platform = new BasicPlatform(platforms.at(j)->y(),platforms.at(j+1)->y());
            if(scene->collidingItems(platform).empty()){
                scene->addItem(platform);
            }
        }
        j++;
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
