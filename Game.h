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
    int const nb_platform = 40;
    int nb_platform_allow = nb_platform;
    bool firstGeneration = true;
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
    float generateRandomPourcent();

public slots:
    void movePlayer();
    void jumpPlayer();


    QList<Platform *> getAllJumpablePlatforms();
};

#endif //DOODLEJUMP_GAME_H
