//
// Created by Benoît on 21/10/2019.
//

#ifndef CROCROJUMP_GAME_H
#define CROCROJUMP_GAME_H

#include <QGraphicsView>
#include "Platform.h"
#include <QMediaPlayer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
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
    QGraphicsScene *highscoresScene;

    QMediaPlayer* bounceSound ;

    void addPlatform();

    void increaseScore(int addedScore = 1);
    static void quickSort(QList<Platform *> &items, int debut, int fin);

    QList<Platform *> collidingPlatforms(Platform *platform);

    QList<Platform *> getAllPlatforms();

    bool disappearingPlatformAllow = false;
    bool explodingPlatformAllow = false;

    int multiplier = 50;

    int dist_min = 0;
    int dist_max = 0;
    int disappearing_max = 0;
    int exploding_max = 0;
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
    QString temp = "";

    QGraphicsTextItem *tableHighScore;

    void highscores();

    QMediaPlayer *fallSound;
    QMediaPlayer *shootSound;
    QMediaPlayer *springSound;
    QMediaPlayer *jetpackSound;
    QMediaPlayer *coinSound;
    QMediaPlayer *jumpOnMonsterSound;
    QMediaPlayer *shootMonsterSound;

    void calculateNumberOfPlatform();

    void setupPlayer();

    void menu();

    QTimer* timerMove;
    QTimer* timerJump;
    QTimer* timerEndGame;
    QThread* jumpThread;
    static float generateRandom();
    QList<Platform *> getAllJumpablePlatforms();

private:
    QTimer* jetpackTimer;
    bool m_lost = false;
public slots:

    void stopJetpack();
    void movePlayer();

    void jumpPlayer();
private slots:
    void start();
    void loose();


    void saveScores(QString scores);
    std::list<int> getHighScore();
};

#endif //CROCROJUMP_GAME_H
