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

Game::Game() {

    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    QPixmap backgroundPixmap = QPixmap();
    bool backgroundLoaded = backgroundPixmap.load(":/images/background.png");
    if (!backgroundLoaded) {
        qDebug() << "Error loading : :/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(backgroundPixmap));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // create a player
    player = new Player();

    text = scene->addText(QString::number(m_score), QFont("Al Seana"));
    text->setPos(10, 10);

    // create platforms
    addPlatform();

    // initialize player on the lowest platform
    setupPlayer();

    fallSound = new QMediaPlayer();
    shootSound = new QMediaPlayer();
    fallSound->setMedia(QUrl("qrc:/sounds/fall.mp3"));
    shootSound->setMedia(QUrl("qrc:/sounds/shoot.mp3"));
    auto * timerMove = new QTimer();
    auto * timerJump = new QTimer();
    connect(timerMove, &QTimer::timeout, this, &Game::movePlayer);
    connect(timerJump, &QTimer::timeout, this, &Game::jumpPlayer);
    timerMove->start(5);
    timerJump->start(10);

}

void Game::calculateNumberOfPlatform() {
    // TODO : faire une énum 1000, 2500 et >= 2500
    if (m_score < 500) {
        nb_platform_allow = nb_platform;
    } else if (m_score < 1000) {
        nb_platform_allow = 30;
    } else
        nb_platform_allow = 20;
}


void Game::addPlatform() {

    int nb_actual_platform = 0;

    calculateNumberOfPlatform();

    for (auto element : scene->items()) {
        if (dynamic_cast<Platform *>(element)) {
            nb_actual_platform++;
        }
    }

    if (nb_actual_platform < nb_platform_allow) {
        int i = 0;
        while (i < nb_platform_allow - nb_actual_platform) {
            int breaking = rand() % static_cast<int>(6 + 1);
            int moving = rand() % static_cast<int>(6 + 1);
            Platform *platform;
            if (breaking == 1)
                platform = new BreakingPlatform();
            else if (moving == 1)
                platform = new MovingPlatform();
            else
                platform = new BasicPlatform();

            if (scene->collidingItems(platform).empty()) {
                scene->addItem(platform);
                i++;
            }
        }

        QList<QGraphicsItem *> platforms;

        for (auto element : scene->items()) {
            if (auto *platform = dynamic_cast<BasicPlatform *>(element)) {
                platforms.append(platform);
            }
        }

        if (!platforms.empty()) {
            quickSort(platforms, 0, platforms.size() - 1);
        }

        int j = 0;
        while (j < platforms.size() - 1) {
            float dist = QLineF(0, platforms.at(j)->y(), 0, platforms.at(j + 1)->y()).length();
            if (dist > 150) {
                auto *platform = new BasicPlatform(platforms.at(j)->y(), platforms.at(j + 1)->y());
                if (scene->collidingItems(platform).empty()) {
                    scene->addItem(platform);

                    // Si - de 2%, on spawn un monstre
                    int probMonster = rand() % 100;
                    if(probMonster <= MONSTER_SPAWN_PROB) {

                        // Recupération
                        auto* monster = new Monster(platform);
                        scene->addItem(monster);
                    }
                }
            }
            j++;
        }

    }


}

void Game::increaseScore() {
    m_score++;
    text->setPlainText(QString::number(m_score));
}

void Game::quickSort(QList<QGraphicsItem *> &items, int low, int high) {

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
            items.swap(i, j);
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
        player->setY(WINDOW_HEIGHT - player->pixmap().height());
        loose();
    }
}

void Game::jumpPlayer() {
    player->m_velocityY += GRAVITY;
    if(player->y() < MAX_HEIGHT) { // Hauteur max, scroll
        isScrolling = true;
        increaseScore();
        player->setY(MAX_HEIGHT);
        for(auto element : scene->items()) {
            if(dynamic_cast<Platform*>(element) || dynamic_cast<Bullet*>(element) || dynamic_cast<Monster*>(element)) {
                element->setY(element->y() - player->m_velocityY);

                if(auto* platform = dynamic_cast<Platform*>(element)) {
                    if (platform->y() > WINDOW_HEIGHT) { // Si plateforme en dessous de l'écran
                        Platform::multiplier = 0.f;
                        addPlatform();
                        scene->removeItem(platform);
                    }
                }
                else if(auto* bullet = dynamic_cast<Bullet*>(element)) {
                    if (bullet->y()+bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                        scene->removeItem(bullet);
                    }
                }
            }
        }
    }
    else {
        // Scrool a little more to prevent scrolling on each jump if player doesn't move
        if(isScrolling) {
            isScrolling = false;
            player->setY(player->y()+1);
            for(auto element : scene->items()) {
                if(dynamic_cast<Platform*>(element) || dynamic_cast<Bullet*>(element) || dynamic_cast<Monster*>(element)) {
                    element->setY(element->y() + 1);
                    if(auto* platform = dynamic_cast<Platform*>(element)) {
                        if (platform->y() > WINDOW_HEIGHT) { // Si plateforme en dessous de l'écran
                            Platform::multiplier = 0.f;
                            addPlatform();
                            scene->removeItem(platform);
                        }
                    }
                    else if(auto* bullet = dynamic_cast<Bullet*>(element)) {
                        if (bullet->y()+bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                            scene->removeItem(bullet);
                        }
                    }
                }
            }
        }
    }
    player->setY(player->y() + player->m_velocityY);

    if (player->m_velocityY > 0) {
        // On vérifie si on touche une plateforme
        for(auto element : scene->collidingItems(player)) {
            auto* platform = dynamic_cast<Platform*>(element);

            if(platform) { // Rebond
                // Si les pieds atteignent la moitié supérieure de la plateforme
                if(player->y()+player->pixmap().height() < platform->y()+platform->pixmap().height()/2) {
                    if(dynamic_cast<BreakingPlatform*>(platform)){
                        auto * breaking = dynamic_cast<BreakingPlatform*>(platform);
                        breaking->launchBreak();
                    }
                    else{
                        player->bounce();
                    }

                }
            }
        }
    }
}

void Game::loose() {
    fallSound->play();
}

void Game::setupPlayer() {
    int maxY = 0;
    Platform* lowestPlatform;

    for (auto element : scene->items()) {
        if (auto* platform = dynamic_cast<Platform *>(element)) {
            if(platform->y() > maxY) {
                maxY = platform->y();
                lowestPlatform = platform;
            }
        }
    }

    player->setPos(lowestPlatform->x(), lowestPlatform->y()-player->pixmap().height());

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(100);

    scene->addItem(player);
}

