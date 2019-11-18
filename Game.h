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

    void increaseScore();

private:
    int m_score = 0;
};

#endif //DOODLEJUMP_GAME_H
