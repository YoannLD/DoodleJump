//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <QGraphicsView>
#include "Platform.h"

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
    int nb_platform_allow;
    int m_score = 0;
    QGraphicsTextItem *text;

    void calculateNumberOfPlatform();

    QList<Platform *> collidingPlatforms(Platform *platform);

    QList<Platform *> getAllPlatforms();
};

#endif //DOODLEJUMP_GAME_H
