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

Game::Game() {

    // create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    QPixmap* backgroundPixmap = new QPixmap();
    bool backgroundLoaded = backgroundPixmap->load(":/images/background.png");
    if (!backgroundLoaded) {
        qDebug() << "Error loading : :/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(*backgroundPixmap));

    delete backgroundPixmap;

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    text = scene->addText(QString::number(m_score), QFont("Al Seana"));
    text->setPos(10, 10);

    fallSound = new QMediaPlayer();
    shootSound = new QMediaPlayer();
    fallSound->setMedia(QUrl("qrc:/sounds/fall.mp3"));
    shootSound->setMedia(QUrl("qrc:/sounds/shoot.mp3"));
    timerMove = new QTimer();
    timerJump = new QTimer();
    connect(timerMove, &QTimer::timeout, this, &Game::movePlayer);
    connect(timerJump, &QTimer::timeout, this, &Game::jumpPlayer);

    start();
}

void Game::start() {

    // Clear scene
    for (auto element : scene->items()) {
        if (dynamic_cast<Platform *>(element) || dynamic_cast<Monster *>(element) || dynamic_cast<Bullet *>(element) || dynamic_cast<Player *>(element)) {
            scene->removeItem(element);
            delete element;
        }
    }
    m_score = 0;
    isScrolling = false;
    nb_platform_allow = nb_platform;
    Platform::multiplier = WINDOW_HEIGHT;

    // create platforms
    addPlatform();

    // initialize player on the lowest platform
    setupPlayer();

    timerMove->start(4);
    timerJump->start(8);
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

QList<Platform*> Game::collidingPlatforms(Platform* platform){
    QList<Platform*> res;
    QList<Platform*> platforms = getAllPlatforms();
    int i = 0;
    while(i < platforms.size()){
        if(MovingPlatform* movingPlatform = dynamic_cast<MovingPlatform*>(platforms.at(i))){
            if(platform->y()+platform->pixmap().height() < movingPlatform->Platform::y() || platform->y() > movingPlatform->Platform::y()+movingPlatform->Platform::pixmap().height()){
            }
            else{
                res.append(movingPlatform);
            }

        }
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


void Game::addPlatform() {

    calculateNumberOfPlatform();
    int nb_actual_platform = getAllPlatforms().size();

    // Chance d'être sur une section disapearingPlatform
    int probDisappearingPlatform = rand() % 100;
    if(probDisappearingPlatform <= DISAPPEARING_PLATFORM_PROB && !sectionDisappearingPlatform){
        sectionDisappearingPlatform = true;
        countNbDisappearingPlatform = 2+ (rand() % static_cast<int>(4+1));
        countNbDisappearingPlatformActual = 0;
        qDebug() << countNbDisappearingPlatform;
    }
    if(countNbDisappearingPlatformActual >= countNbDisappearingPlatform)
        sectionDisappearingPlatform = false;

    if(nb_actual_platform < nb_platform_allow) {
        int i = 0;
        if(sectionDisappearingPlatform){
            while(i < nb_platform_allow - nb_actual_platform){
                Platform *platform = new DisappearingPlatform();
                if(scene->collidingItems(platform).empty() && collidingPlatforms(platform).empty()){
                    scene->addItem(platform);
                    countNbDisappearingPlatformActual++;
                    i++;
                }
            }
        }
        else{
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

                if(dynamic_cast<MovingPlatform*>(platform)) {
                    QGraphicsRectItem* rect = new QGraphicsRectItem(0,platform->y(),WINDOW_WIDTH,platform->pixmap().height());
                    if(scene->collidingItems(rect).empty()){
                        scene->addItem(platform);
                        i++;
                    }

                }
                else {
                    if (scene->collidingItems(platform).empty() && collidingPlatforms(platform).empty() ) {
                        scene->addItem(platform);
                        i++;
                        if(auto* element = dynamic_cast<BasicPlatform*>(platform)) {
                            // Si - de 2%, on spawn un monstre
                            int probMonster = rand() % 100;
                            if (probMonster <= MONSTER_SPAWN_PROB) {

                                // Recupération
                                auto *monster = new Monster(element);
                                scene->addItem(monster);
                            }
                        }
                    }
                }
            }
        }


        QList<QGraphicsItem *> platforms;

        // Répertorie toutes les plateformes on l'on peut sauter
        for(auto element : scene->items()) {
            if(dynamic_cast<BasicPlatform*>(element) || dynamic_cast<MovingPlatform*>(element) || dynamic_cast<DisappearingPlatform*>(element)){
                platforms.append(element);
            }
        }

        // Trie de haut en bas les plateformes on l'on peut sauter
        if (!platforms.empty()) {
            quickSort(platforms, 0, platforms.size() - 1);
        }

        // On regarde si chaque plateforme est au plus de 130
        float distMax = 120.f;
        int j = 0;
        while (j < platforms.size() - 1) {
            float dist = QLineF(0, platforms.at(j)->y(), 0, platforms.at(j + 1)->y()).length();
            if (dist > distMax) {
                Platform *platform;
                if(sectionDisappearingPlatform){
                    platform = new DisappearingPlatform(platforms.at(j)->y(), platforms.at(j + 1)->y());
                    countNbDisappearingPlatformActual++;
                }
                else{
                    platform = new BasicPlatform(platforms.at(j)->y(), platforms.at(j + 1)->y());
                }

                if (scene->collidingItems(platform).empty()) {
                    scene->addItem(platform);

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
            if(dynamic_cast<Platform*>(element) || dynamic_cast<Bullet*>(element) || dynamic_cast<Monster*>(element)) {
                element->setY(element->y() - player->getVelocityY());

                if(auto* platform = dynamic_cast<Platform*>(element)) {
                    if (platform->y() > WINDOW_HEIGHT) { // Si plateforme en dessous de l'écran
                        Platform::multiplier = 0.f;
                        addPlatform();
                        scene->removeItem(platform);
                        delete platform;
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
                            delete platform;
                        }
                    }
                    else if(auto* bullet = dynamic_cast<Bullet*>(element)) {
                        if (bullet->y()+bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                            scene->removeItem(bullet);
                            delete platform;
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
            auto* platform = dynamic_cast<Platform*>(element);

            if(platform) { // Rebond
                // Si les pieds atteignent la moitié supérieure de la plateforme
                if(player->y()+player->pixmap().height() < platform->y()+platform->pixmap().height()/2) {
                    if(dynamic_cast<BreakingPlatform*>(platform)){
                        auto * breaking = dynamic_cast<BreakingPlatform*>(platform);
                        breaking->launchBreak();
                    }
                    else if(dynamic_cast<DisappearingPlatform*>(platform)){
                        player->bounce();
                        scene->removeItem(platform);
                        delete platform;
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
    timerMove->stop();
    timerJump->stop();
    fallSound->play();
    start();
}

void Game::setupPlayer() {
    int maxY = 0;
    Platform* lowestPlatform;

    for (auto element : scene->items()) {
        if (auto* platform = dynamic_cast<BasicPlatform *>(element)) {
            if(platform->y() > maxY && platform->y() < 600) {
                maxY = platform->y();
                lowestPlatform = platform;
            }
        }
    }

    // create a player
    player = new Player();
    qDebug() << "Lowest plat: " << lowestPlatform->y();
    player->setPos(lowestPlatform->x(), lowestPlatform->y()-player->pixmap().height());

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setZValue(100);

    scene->addItem(player);
}

