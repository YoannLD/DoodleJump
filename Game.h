//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <QGraphicsView>

class Game: public QGraphicsView{
public:
    // member functions
    Game();

    // member attributes
    QGraphicsScene * scene;

    void addPlatform();
    void increaseScore();
    int getNbPlateformsAllow();
    static void quickSort(QList<QGraphicsItem *> &items, int debut, int fin);


private:
    int nb_platform;
    int m_score = 0;
    QGraphicsTextItem *text;
};

#endif //DOODLEJUMP_GAME_H
