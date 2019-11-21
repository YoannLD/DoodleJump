//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <QGraphicsView>
#include "Platform.h"
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
    static void quickSort(QList<Platform *> &items, int debut, int fin);

    QList<Platform *> collidingPlatforms(Platform *platform);

    QList<Platform *> getAllPlatforms();

private:
    bool isScrolling = false;
    bool sectionDisappearingPlatform = false;
    int countNbDisappearingPlatform;
    int countNbDisappearingPlatformActual;
    int m_score = 0;
    Player* player;
    QGraphicsTextItem *text;
    void loose();
    QMediaPlayer* fallSound ;
    QMediaPlayer* shootSound ;
    void calculateNumberOfPlatform();
    void setupPlayer();
    void start();
    QTimer* timerMove;
    QTimer* timerJump;
    static float generateRandomPourcent();
    QList<Platform *> getAllJumpablePlatforms();

public slots:
    void movePlayer();
    void jumpPlayer();



};

#endif //DOODLEJUMP_GAME_H
