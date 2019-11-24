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
#include "Monster.h"
#include "Bullet.h"
#include "DisappearingPlatform.h"
#include "ExplodingPlatform.h"
#include "Spring.h"

Game::Game() {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    auto* backgroundPixmap = new QPixmap();
    bool backgroundLoaded = backgroundPixmap->load(":/images/background.png");
    if (!backgroundLoaded) {
        qDebug() << "Error loading : :/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(*backgroundPixmap));

    delete backgroundPixmap;

    setScene(scene);

    // --------- Setting up sound effects -------------
    fallSound = new QMediaPlayer();
    shootSound = new QMediaPlayer();
    bounceSound = new QMediaPlayer();
    springSound = new QMediaPlayer();
    springSound->setMedia(QUrl("qrc:/sounds/spring.mp3"));
    bounceSound->setMedia(QUrl("qrc:/sounds/jump.mp3"));
    fallSound->setMedia(QUrl("qrc:/sounds/fall.mp3"));
    shootSound->setMedia(QUrl("qrc:/sounds/shoot.mp3"));
    timerMove = new QTimer();
    timerJump = new QTimer();
    connect(timerMove, &QTimer::timeout, this, &Game::movePlayer);
    connect(timerJump, &QTimer::timeout, this, &Game::jumpPlayer);

    start();
}

void Game::start() {

    m_score = 0;
    text = scene->addText(QString::number(m_score), QFont("Al Seana"));
    text->setPos(10, 10);
    isScrolling = false;

    // create platforms
    addPlatform();

    // initialize player on the lowest platform
    setupPlayer();

    timerMove->start(4);
    timerJump->start(8);
}

void Game::calculateNumberOfPlatform() {
    if (m_score < 500) {
        dist_min = 0;
        dist_max = 50;
        disappearingPlatformAllow = false;
        explodingPlatformAllow = false;
    } else if (m_score <= 1000) {
        dist_min = 10;
        dist_max = 60;
        disappearingPlatformAllow = true;
    } else if (m_score <= 2000) {
        dist_min = 20;
        dist_max = 60;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if (m_score <= 2500) {
        dist_min = 40;
        dist_max = 60;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if (m_score <= 2700) {
        dist_min = 40;
        dist_max = 65;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if(m_score > 3000){
        dist_min = 80;
        dist_max = 90;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    }

}

QList<Platform*> Game::collidingPlatforms(Platform* platform){
    QList<Platform*> res;
    QList<Platform*> platforms = getAllPlatforms();
    int i = 0;
    while(i < platforms.size()){
        if(auto* movingPlatform = dynamic_cast<MovingPlatform*>(platforms.at(i)))
            if(!((platform->y()+platform->pixmap().height() < movingPlatform->Platform::y() || platform->y() > movingPlatform->Platform::y()+movingPlatform->Platform::pixmap().height())))
                res.append(movingPlatform);
        i++;
    }
    return res;
}

QList<Platform*> Game::getAllPlatforms(){
    QList<Platform*> platforms;
    for(auto element : scene->items()) {
        if(auto* platform = dynamic_cast<Platform*>(element)){
            platforms.append(platform);
        }
    }
    return platforms;
}

QList<Platform*> Game::getAllJumpablePlatforms() {
    QList<Platform *> platforms;
    for(auto element : scene->items())
        if(auto* platform = dynamic_cast<Platform*>(element))
            if(dynamic_cast<BasicPlatform*>(platform) || dynamic_cast<MovingPlatform*>(platform) || dynamic_cast<DisappearingPlatform*>(platform) || dynamic_cast<ExplodingPlatform*>(platform))
                platforms.append(platform);

    if (!platforms.empty())
        quickSort(platforms, 0, platforms.size() - 1);

    return platforms;
}

float Game::generateRandom(){
    return rand() % 100;
}

void Game::addPlatform() {

    calculateNumberOfPlatform();

    QList<Platform *> jumpablePlatforms = getAllJumpablePlatforms();
    if (jumpablePlatforms.empty()) {
        auto* temp = new BasicPlatform();
        Platform *platform = new BasicPlatform(WINDOW_HEIGHT - DIST_MAX, (float)WINDOW_HEIGHT-(float)temp->pixmap().height());
        if (scene->collidingItems(platform).empty()) {
            scene->addItem(platform);
            jumpablePlatforms = getAllJumpablePlatforms();
        }
        delete temp;
    }

    int i = 0;

    while(i < jumpablePlatforms.size()){
        if(auto* platform = dynamic_cast<ExplodingPlatform*>(jumpablePlatforms.at(i)))
            if(platform->y() - 100 >= player->y()){
                platform->lauchExplosing();
            }


        i++;
    }

    while (jumpablePlatforms.at(0)->y() > -WINDOW_HEIGHT) {
        if(generateRandom() < DISAPPEARING_PLATFORM_PROB && !sectionDisappearingPlatform && disappearingPlatformAllow){
            sectionDisappearingPlatform = true;
            countNbDisappearingPlatform = 2 + (rand() % static_cast<int>(4+1));
            countNbDisappearingPlatformActual = 0;
        }
        else if (generateRandom() < EXPLODING_PLATFORM_PROB && !sectionExplodingPlatform && explodingPlatformAllow){
                sectionExplodingPlatform = true;
                countNbExplodingPlatform = 2 + (rand() % static_cast<int>(6+1));
                countNbExplodingPlatformActual = 0;
        }

        if(countNbDisappearingPlatformActual >= countNbDisappearingPlatform)
            sectionDisappearingPlatform = false;


        if(countNbExplodingPlatformActual >= countNbExplodingPlatform)
            sectionExplodingPlatform = false;

        auto *lastPlatform = jumpablePlatforms.at(0);
        Platform *platform;
        int margin = 0;
        if(dynamic_cast<MovingPlatform*>(lastPlatform)){
            margin = lastPlatform->pixmap().height();
        }
        if(sectionDisappearingPlatform) {
            if (generateRandom() <= BREAKING_PLATFORM_PROB)
                platform = new BreakingPlatform(lastPlatform->y() - dist_max + margin ,
                                                lastPlatform->y() - margin - dist_min);
            else platform = new DisappearingPlatform(lastPlatform->y() - dist_max + margin ,
                                                    lastPlatform->y() - margin - dist_min);
        }
        else if(sectionExplodingPlatform) {
           platform = new ExplodingPlatform(lastPlatform->y() - dist_max + margin ,
                                                     lastPlatform->y() - margin - dist_min);
        }
        else {
            if (generateRandom() <= BREAKING_PLATFORM_PROB)
                platform = new BreakingPlatform(lastPlatform->y() - dist_max + margin ,
                                                lastPlatform->y() - margin - dist_min);
            else if (generateRandom() <= MOVING_PLATFORM_PROB)
                platform = new MovingPlatform(lastPlatform->y() - dist_max + lastPlatform->pixmap().height(),
                                              lastPlatform->y() - lastPlatform->pixmap().height() - dist_min);
            else
                platform = new BasicPlatform(lastPlatform->y() - dist_max + margin,
                                             lastPlatform->y() - margin - dist_min);
        }

        if(dynamic_cast<MovingPlatform*>(platform)) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0,platform->y(),WINDOW_WIDTH,platform->pixmap().height());
            if(scene->collidingItems(rect).empty()){
                scene->addItem(platform);
                jumpablePlatforms = getAllJumpablePlatforms();
            } else
                delete platform;


            delete rect;

        }
        else if (scene->collidingItems(platform).empty() && collidingPlatforms(platform).empty()) {
            scene->addItem(platform);
            if(dynamic_cast<DisappearingPlatform*>(platform))
                countNbDisappearingPlatformActual++;
            else if(dynamic_cast<ExplodingPlatform*>(platform))
                countNbExplodingPlatformActual++;
            else if(auto* basicPlatform = dynamic_cast<BasicPlatform*>(platform)) {
                if(generateRandom() <= SPRING_PROB) {
                    auto* spring = new Spring(basicPlatform);
                    scene->addItem(spring);
                }
                if(generateRandom() <= MONSTER_SPAWN_PROB) {
                    auto* monster = new Monster(basicPlatform);
                    scene->addItem(monster);
                }
            }
            jumpablePlatforms = getAllJumpablePlatforms();
       }
        else
            delete platform;


    }


}

void Game::increaseScore() {
    m_score++;
    text->setPlainText(QString::number(m_score));
}

void Game::quickSort(QList<Platform *> &items, int low, int high) {

    int i = low;
    int j = high;
    double pivot = items.at((i + j) / 2)->y() + 1000;

    while (i <= j) {
        while (items.at(i)->y() + 1000 < pivot) {
            i++;
        }
        while (items.at(j)->y() + 1000 > pivot) {
            j--;
        }
        if (i <= j) {
            items.swapItemsAt(i,j);
            //items.swap(i,j);
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(items, low, j);
    if (i < high)
        quickSort(items, i, high);

}

void Game::movePlayer() {
    for (int key : player->m_events) {
        switch(key) {
            case Qt::Key_Left :
            case Qt::Key_Q :
                if (player->x() + (player->pixmap().width() / 2) > 0)
                    player->setPos(player->x() - 1, player->y());
                else
                    player->setPos(scene->width() - (player->pixmap().width() / 2), player->y());

                if (!player->m_facingLeft) {
                    player->m_facingLeft = true;
                    player->setPixmap(player->pixmap().transformed(QTransform().scale(-1, 1)));
                }
                break;
            case Qt::Key_Right :
            case Qt::Key_D :
                if (player->x() + (player->pixmap().width() / 2) < scene->width()) {
                    player->setX(player->x() + 1);
                }
                else {
                    player->setX(-player->pixmap().width() / 2);
                }

                if (player->m_facingLeft) {
                    player->m_facingLeft = false;
                    player->setPixmap(player->pixmap().transformed(QTransform().scale(-1, 1)));
                }
                break;
            case Qt::Key_Space:
            case Qt::Key_Up:
            case Qt::Key_Z :
                if(!player->m_hasShot) {
                    player->m_hasShot = true;
                    auto *bullet = new Bullet(player->m_shootTimer);
                    bullet->setPos(player->x() + player->pixmap().width() / 2, player->y());
                    scene->addItem(bullet);

                    player->setPixmap(*player->m_shootingPixmap);
                    // Si le son est déjà lancé, remet à 0
                    if(shootSound->state() == QMediaPlayer::PlayingState) {
                        shootSound->setPosition(0);
                    }
                    else if(shootSound->state() == QMediaPlayer::StoppedState) {
                        shootSound->play();
                    }
                    player->m_shootingPixmapTimer->start(300);
                }
                break;
        }
    }
    if (player->y() + player->pixmap().height()>= WINDOW_HEIGHT) { // (Perdu)
        fallSound->play();
        loose();
    }
}

void Game::jumpPlayer() {
    player->setVelocityY(player->getVelocityY() + GRAVITY);

    if(player->y() < MAX_HEIGHT) { // Hauteur max, scroll
        isScrolling = true;
        increaseScore();
        player->setY(MAX_HEIGHT);
        for(auto element : scene->items()) {
            if(dynamic_cast<Platform*>(element) || dynamic_cast<Bullet*>(element) || dynamic_cast<Monster*>(element) || dynamic_cast<Bonus*>(element)) {
                element->setY(element->y() - player->getVelocityY());

                if(dynamic_cast<Platform*>(element) || dynamic_cast<Bonus*>(element)) {
                    if (element->y() > WINDOW_HEIGHT) { // Si plateforme ou bonus en dessous de l'écran
                        scene->removeItem(element);
                        delete element;
                    }

                }
                else if(auto* bullet = dynamic_cast<Bullet*>(element)) {
                    if (bullet->y()+bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                        scene->removeItem(bullet);
                        delete bullet;
                    }
                }
            }
        }
    }
    else {
        // Scrool a little more to prevent scrolling on each jump if player doesn't move
        if(isScrolling) {
            addPlatform();
            isScrolling = false;
            player->setY(player->y()+1);
            for(auto element : scene->items()) {
                if(dynamic_cast<Platform*>(element) || dynamic_cast<Bullet*>(element) || dynamic_cast<Monster*>(element) || dynamic_cast<Bonus*>(element)) {
                    element->setY(element->y() + 1);
                    if(dynamic_cast<Platform*>(element)) {
                        if (element->y() > WINDOW_HEIGHT) { // Si plateforme/bonus en dessous de l'écran
                            scene->removeItem(element);
                            delete element;
                        }
                    }
                    else if(auto* bullet = dynamic_cast<Bullet*>(element)) {
                        if (bullet->y()+bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                            scene->removeItem(bullet);
                            delete bullet;
                        }
                    }
                }
            }
        }
    }
    player->setY(player->y() + player->getVelocityY());

    if (player->getVelocityY() > 0) {
        // On vérifie si on touche une plateforme
        for(auto element : scene->collidingItems(player)) {
            if(auto* platform = dynamic_cast<Platform*>(element)) { // Rebond
                // Si les pieds atteignent la moitié supérieure de la plateforme
                if(player->y()+player->pixmap().height() < platform->y()+platform->pixmap().height()/2) {
                    if(dynamic_cast<BreakingPlatform*>(platform)){
                        auto * breaking = dynamic_cast<BreakingPlatform*>(platform);
                        breaking->launchBreak();
                    }
                    else if(dynamic_cast<DisappearingPlatform*>(platform)){
                        player->bounce(-5);
                        scene->removeItem(platform);
                        delete platform;

                        // Si le son est déjà lancé, remet à 0
                        if (bounceSound->state() == QMediaPlayer::PlayingState) {
                            bounceSound->setPosition(0);
                        } else if (bounceSound->state() == QMediaPlayer::StoppedState) {
                            bounceSound->play();
                        }
                    }
                    else{
                        player->bounce(-5);

                        // Si le son est déjà lancé, remet à 0
                        if (bounceSound->state() == QMediaPlayer::PlayingState) {
                            bounceSound->setPosition(0);
                        } else if (bounceSound->state() == QMediaPlayer::StoppedState) {
                            bounceSound->play();
                        }
                    }

                }
            }
            else if(auto* monster = dynamic_cast<Monster*>(element)) { // Monstre
                if(player->y()+player->pixmap().height() < monster->y()+monster->pixmap().height()/2) {
                    monster->launchKill();
                    player->bounce(-7);
                    increaseScore();
                }
                else {
                    loose();
                }
            }
            else if(auto* bonus = dynamic_cast<Bonus*>(element)) { // Rebond
                if(auto* spring = dynamic_cast<Spring*>(bonus)) {
                    if(player->y()+player->pixmap().height() < spring->y()+spring->pixmap().height()/2) {
                        player->bounce(-10);

                        // Si le son est déjà lancé, remet à 0
                        if (springSound->state() == QMediaPlayer::PlayingState) {
                            springSound->setPosition(0);
                        } else if (springSound->state() == QMediaPlayer::StoppedState) {
                            springSound->play();
                        }
                        spring->jump();
                    }
                }
            }
        }
    }
    else {
        // On vérifie si on touche un monstre
        for(auto element : scene->collidingItems(player)) {
            if (dynamic_cast<Monster*>(element)) { // Monstre
                loose();
            }
        }
    }
}

void Game::loose() {
    timerMove->stop();
    timerJump->stop();
    // Clear scene
    for (auto element : scene->items()) { // dynamic_cast<GameObject *>(element) ?
        if (dynamic_cast<Platform *>(element) || dynamic_cast<Monster *>(element) ||
            dynamic_cast<Bullet *>(element) || dynamic_cast<Player *>(element) || dynamic_cast<Bonus *>(element) ||dynamic_cast<QGraphicsTextItem*>(element)) {
            scene->removeItem(element);
            delete element;
        }
    }
    start();
}

void Game::setupPlayer() {
    Platform* lowestPlatform = getAllJumpablePlatforms().last();

    // create a player
    player = new Player();
    player->setPos(lowestPlatform->x(), lowestPlatform->y()-player->pixmap().height());

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(100);

    scene->addItem(player);
}

