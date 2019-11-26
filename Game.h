//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <QGraphicsView>
#include "Platform.h"
#include <QMediaPlayer>
#include <QtWidgets/QPushButton>
#include "Player.h"

class Game :  public QGraphicsView {
    Q_OBJECT
public:
    Game();

private:

    QPushButton *buttonPlay;
    QPushButton *buttonQuit;

    QGraphicsScene *scene;
    QGraphicsScene *menuScene;
    QMediaPlayer* bounceSound ;

    void addPlatform();

    void increaseScore();
    static void quickSort(QList<Platform *> &items, int debut, int fin);

    QList<Platform *> collidingPlatforms(Platform *platform);

    QList<Platform *> getAllPlatforms();

    bool disappearingPlatformAllow = false;
    bool explodingPlatformAllow = false;

    int multiplier = 50;

    int dist_min = 0;
    int dist_max = 0;
    bool isScrolling = false;

    bool sectionDisappearingPlatform = false;
    int countNbDisappearingPlatform;
    int countNbDisappearingPlatformActual;

    bool sectionExplodingPlatform = false;
    int countNbExplodingPlatform;
    int countNbExplodingPlatformActual;

    int m_score = 0;
    Player *player;
    QGraphicsTextItem *text;

    void loose();

    QMediaPlayer *fallSound;
    QMediaPlayer *shootSound;
    QMediaPlayer *springSound;

    void calculateNumberOfPlatform();

    void setupPlayer();

    void menu();
    QTimer* timerMove;
    QTimer* timerJump;
    static float generateRandom();
    QList<Platform *> getAllJumpablePlatforms();

public slots:

    void movePlayer();

    void jumpPlayer();
private slots:
    void start();



};

#endif //DOODLEJUMP_GAME_H
