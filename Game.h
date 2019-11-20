//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include "Player.h"

class Game: public QGraphicsView{
public:
    // member functions
    Game();

    // member attributes
    QGraphicsScene * scene;

    void addPlatform();
    void increaseScore();
    static void quickSort(QList<QGraphicsItem *> &items, int debut, int fin);



private:
    int const nb_platform = 40;
    int nb_platform_allow = nb_platform;
    bool isScrolling = false;
    int m_score = 0;
    Player* player;
    QGraphicsTextItem *text;
    void loose();
    QMediaPlayer* fallSound ;
    QMediaPlayer* shootSound ;
    void calculateNumberOfPlatform();
    void setupPlayer();

public slots:
    void movePlayer();
    void jumpPlayer();
};

#endif //DOODLEJUMP_GAME_H
