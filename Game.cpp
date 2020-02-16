#include "Game.h"
#include "Player.h"
#include "BasicPlatform.h"
#include <QGraphicsScene>
#include <QPushButton>
#include <QDebug>
#include <QThread>
#include <QElapsedTimer>
#include <QScreen>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "consts.h"
#include "BreakingPlatform.h"
#include "MovingPlatform.h"
#include "Monster.h"
#include "Bullet.h"
#include "DisappearingPlatform.h"
#include "ExplodingPlatform.h"
#include "Spring.h"
#include "Jetpack.h"
#include "Resources.h"
#include "coin.h"
#include <chrono>
#include <functional>
#include <list>
#include <QRandomGenerator>
#include <QtGui/QFontDatabase>


Game::Game() {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // ------------- SCENE DE JEU
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    scene->setBackgroundBrush(QBrush(QPixmap(QString(":/images/background.png"))));

    auto* hab = new QGraphicsPixmapItem();
    hab->setPixmap(Resources::png("habillage.png"));
    hab->setEnabled(false);

    scene->addItem(hab);
    hab->setZValue(150);

    // -------------- SCENE MENU
    menuScene = new QGraphicsScene(this);
    menuScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    auto* menuPixmap = new QPixmap();
    bool backgroundLoaded = menuPixmap->load(":/images/menuG.png");
    if (!backgroundLoaded) {
        qDebug() << "Error loading : :/images/menuG.png";
    }

    menuScene->setBackgroundBrush(QBrush(*menuPixmap));


    // -------------- SCENE HIGHSCORES
    highscoresScene = new QGraphicsScene(this);
    highscoresScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    menuPixmap = new QPixmap();
    backgroundLoaded = menuPixmap->load(":/images/menuG.png");
    if (!backgroundLoaded) {
        qDebug() << "Error loading : :/images/menuG.png";
    }

    highscoresScene->setBackgroundBrush(QBrush(*menuPixmap));
    tableHighScore = new QGraphicsTextItem();
    tableHighScore = highscoresScene->addText(temp);

    delete menuPixmap;

    QFontDatabase::addApplicationFont(":/fonts/al-seana.ttf");

    // --------- Setting up sound effects -------------
    fallSound = new QMediaPlayer();
    rageSound = new QMediaPlayer();
    shootSound = new QMediaPlayer();
    bounceSound = new QMediaPlayer();
    coinSound = new QMediaPlayer();
    springSound = new QMediaPlayer();
    jetpackSound = new QMediaPlayer();
    jumpOnMonsterSound = new QMediaPlayer();
    shootMonsterSound = new QMediaPlayer();

    shootMonsterSound->setMedia(QUrl("qrc:/sounds/killMonster.mp3"));
    jumpOnMonsterSound->setMedia(QUrl("qrc:/sounds/jumpMonster.mp3"));
    jetpackSound->setMedia(QUrl("qrc:/sounds/jetpack.mp3"));
    springSound->setMedia(QUrl("qrc:/sounds/spring.mp3"));
    bounceSound->setMedia(QUrl("qrc:/sounds/jump.mp3"));
    coinSound->setMedia(QUrl("qrc:/sounds/coin.mp3"));
    fallSound->setMedia(QUrl("qrc:/sounds/fall.mp3"));
    rageSound->setMedia(QUrl("qrc:/sounds/putain.mp3"));
    shootSound->setMedia(QUrl("qrc:/sounds/shoot.mp3"));



    timerMove = new QTimer();
    timerJump = new QTimer();
    timerEndGame = new QTimer();
    jetpackTimer = new QTimer();
    jetpackTimer->setSingleShot(true);
    timerEndGame->setSingleShot(true);
    jumpThread = new QThread(this);
    timerJump->moveToThread(jumpThread);
    timerJump->setInterval(8);
    connect(jumpThread, SIGNAL(started()), timerJump, SLOT(start()));
    connect(jumpThread, SIGNAL(finished()), timerJump, SLOT(stop()));
    connect(timerMove, &QTimer::timeout, this, &Game::movePlayer);
    connect(timerJump, &QTimer::timeout, this, &Game::jumpPlayer);
    connect(timerEndGame, &QTimer::timeout, this, &Game::loose);
    connect(jetpackTimer, &QTimer::timeout, this, &Game::stopJetpack);

    menu();
}


void Game::menu() {

    setScene(menuScene);

    int weight = 200;

    buttonPlay = new QPushButton("Jouer", this);

    buttonPlay->setGeometry(WINDOW_WIDTH/2-weight/2,280,weight,50);
    buttonPlay->isFlat();
    buttonPlay->setObjectName("playButton");
    buttonPlay->setFont(QFont("Al-seana",45,QFont::Bold));
    buttonPlay->setStyleSheet("QPushButton {background-color: transparent; color = black} QPushButton#playButton:hover {color: #a41101}");

    buttonQuit = new QPushButton("Quitter", this);
    buttonQuit->setGeometry(WINDOW_WIDTH/2-weight/2,400,weight,50);
    buttonQuit->isFlat();
    buttonQuit->setObjectName("buttonQuit");
    buttonQuit->setFont(QFont("Al-seana",45,QFont::Bold));
    buttonQuit->setStyleSheet("QPushButton {background-color: transparent; color = black} QPushButton#buttonQuit:hover {color: #a41101}");

    buttonPlay->setVisible(true);
    buttonQuit->setVisible(true);

    connect(buttonPlay, SIGNAL (released()),this, SLOT (start()));
    connect(buttonQuit, SIGNAL (released()),qApp, SLOT (quit()));

}

void Game::highscores() {

    std::list<int> scores = getHighScore();


    // On regarde si le score actuel fait partie des meilleurs scores
    if(scores.back() < m_score){
        scores.push_back(m_score);
        scores.sort(std::greater<int>());
        scores.pop_back();
    }

    temp = "";
    for(int score : scores)
        temp.append(QString::number(score).append("\r\n"));

    Game::saveScores(temp);


    tableHighScore->setFont(QFont("Al-seana",40,QFont::Bold));
    tableHighScore->setPos(580,245);
    tableHighScore->setPlainText(temp);



    setScene(highscoresScene);


    buttonPlay = new QPushButton("Recommencer", this);

    buttonPlay->setGeometry(550,550,200,45);
    buttonPlay->isFlat();
    buttonPlay->setObjectName("playButton");
    buttonPlay->setFont(QFont("Al-seana",25,QFont::Bold));
    buttonPlay->setStyleSheet("QPushButton {background-color: transparent; color = black} QPushButton#playButton:hover {color: #a41101}");

    buttonQuit = new QPushButton("Quitter", this);
    buttonQuit->setGeometry(445,630,120,45);
    buttonQuit->isFlat();
    buttonQuit->setObjectName("buttonQuit");
    buttonQuit->setFont(QFont("Al-seana",25,QFont::Bold));
    buttonQuit->setStyleSheet("QPushButton {background-color: transparent; color = black} QPushButton#buttonQuit:hover {color: #a41101}");

    buttonPlay->setVisible(true);
    buttonQuit->setVisible(true);

    connect(buttonPlay, SIGNAL (released()),this, SLOT (start()));
    connect(buttonQuit, SIGNAL (released()),qApp, SLOT (quit()));

}

void Game::start() {

    buttonPlay->setVisible(false);
    buttonQuit->setVisible(false);

    setScene(scene);

    m_score = 0;
    m_lost = false;
    text = scene->addText(QString::number(m_score), QFont("Al-seana",30,QFont::Bold));
    text->setPos(100, 60);
    text->setZValue(200);
    isScrolling = false;

    // create platforms
    addPlatform();

    // initialize player on the lowest platform
    setupPlayer();

    timerMove->start(4);
    jumpThread->start();
}

void Game::calculateNumberOfPlatform() {
    if (m_score < 3000) {
        dist_min = 0;
        dist_max = 50;
        disappearingPlatformAllow = false;
        explodingPlatformAllow = false;
    } else if (m_score <= 5000) {
        dist_min = 10;
        dist_max = 60;
        disappearing_max = 4;
        disappearingPlatformAllow = true;
    } else if (m_score <= 10000) {
        dist_min = 20;
        dist_max = 60;
        disappearing_max = 5;
        exploding_max = 2;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if (m_score <= 11000) {
        dist_min = 40;
        dist_max = 60;
        disappearing_max = 5;
        exploding_max = 3;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if (m_score <= 12000) {
        dist_min = 40;
        dist_max = 65;
        disappearing_max = 5;
        exploding_max = 6;
        explodingPlatformAllow = true;
        disappearingPlatformAllow = true;
    } else if(m_score > 14000){
        dist_min = 80;
        dist_max = 85;
        disappearing_max = 6;
        exploding_max = 8;
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
    return QRandomGenerator::global()->bounded((double) 100);
}

void Game::addPlatform() {
    auto start = std::chrono::high_resolution_clock::now();

    calculateNumberOfPlatform();

    QList<Platform *> jumpablePlatforms = getAllJumpablePlatforms();
    if (jumpablePlatforms.empty()) {
        auto* temp = new BasicPlatform();
        Platform *platform = new BasicPlatform(WINDOW_HEIGHT - DIST_MAX, (float)WINDOW_HEIGHT-(float)temp->pixmap().height());
        QList<QGraphicsItem *> items = scene->collidingItems(platform);
        if (items.empty()) {
            scene->addItem(platform);
            jumpablePlatforms = getAllJumpablePlatforms();
        }
        else if(items.size() == 1)
            if(!dynamic_cast<Platform*>(items.at(0))) {
                scene->addItem(platform);
                jumpablePlatforms = getAllJumpablePlatforms();
            }

        delete temp;
    }

    int i = 0;

    while(i < jumpablePlatforms.size()){
        if(auto* platform = dynamic_cast<ExplodingPlatform*>(jumpablePlatforms.at(i))){
            auto* plat = dynamic_cast<GameObject*>(jumpablePlatforms.at(i));
            auto* play = dynamic_cast<GameObject*>(player);
            if(plat->operator<(play)){
                platform->launchExplosing();
            }

        }



        i++;
    }

    while (jumpablePlatforms.at(0)->y() > -WINDOW_HEIGHT*multiplier) {
        multiplier = 1;
        if(generateRandom() < DISAPPEARING_PLATFORM_PROB && !sectionDisappearingPlatform && disappearingPlatformAllow){
            sectionDisappearingPlatform = true;
            countNbDisappearingPlatform = (rand() % static_cast<int>(disappearing_max+1));
            countNbDisappearingPlatformActual = 0;
        }
        else if (generateRandom() < EXPLODING_PLATFORM_PROB && !sectionExplodingPlatform && explodingPlatformAllow){
                sectionExplodingPlatform = true;
                countNbExplodingPlatform = (rand() % static_cast<int>(exploding_max+1));
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

        QList<QGraphicsItem *> itemsColliding = scene->collidingItems(platform);
        bool plateformColliding = collidingPlatforms(platform).empty();

        // Dans le cas d'une plateforme mouvante
        if(dynamic_cast<MovingPlatform*>(platform)) {
            QGraphicsRectItem* rect = new QGraphicsRectItem(0,platform->y(),WINDOW_WIDTH,platform->pixmap().height());
            QList<QGraphicsItem *> items = scene->collidingItems(rect);
            if(items.empty()){
                scene->addItem(platform);
                jumpablePlatforms = getAllJumpablePlatforms();
            } else if(items.size() == 1)
                if(!dynamic_cast<Platform*>(items.at(0))) {
                    scene->addItem(platform);
                    jumpablePlatforms = getAllJumpablePlatforms();
                }
                else
                    delete platform;
            else
                delete platform;


            delete rect;

        }
        else if ((itemsColliding.empty() && plateformColliding) || (itemsColliding.size() == 1 && plateformColliding &&
                !dynamic_cast<Platform *>(itemsColliding.at(0)))) {
            scene->addItem(platform);
            if(dynamic_cast<DisappearingPlatform*>(platform))
                countNbDisappearingPlatformActual++;
            else if(dynamic_cast<ExplodingPlatform*>(platform))
                countNbExplodingPlatformActual++;
            jumpablePlatforms = getAllJumpablePlatforms();
       }
        else
            delete platform;

        if(dynamic_cast<BasicPlatform*>(platform) || dynamic_cast<MovingPlatform*>(platform)) {
            if(generateRandom() <= JETPACK_PROB && !player->isOnJetpack()) {
                auto* jetpack = new Jetpack(platform);
                scene->addItem(jetpack);
                if(auto* movingPlatform = dynamic_cast<MovingPlatform*>(platform)) {
                    movingPlatform->addAssociatedItem(jetpack);
                }
            }
            else if(generateRandom() <= SPRING_PROB) {
                auto* spring = new Spring(platform);
                scene->addItem(spring);
                if(auto* movingPlatform = dynamic_cast<MovingPlatform*>(platform)) {
                    movingPlatform->addAssociatedItem(spring);
                }
            }
            else if(generateRandom() <= MONSTER_SPAWN_PROB) {
                auto* monster = new Monster(platform);
                scene->addItem(monster);
                if(auto* movingPlatform = dynamic_cast<MovingPlatform*>(platform)) {
                    movingPlatform->addAssociatedItem(monster);
                }
            }
            else if(generateRandom() <= COIN_PROB) {
                auto* coin = new Coin(platform);
                scene->addItem(coin);
                if(auto* movingPlatform = dynamic_cast<MovingPlatform*>(platform)) {
                    movingPlatform->addAssociatedItem(coin);
                }
            }
        }


    }
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    //qDebug() << duration.count();

}

std::list<int> Game::getHighScore(){

    std::list<int> listOfScores;
    QString data;
    QString fileName("highscores.txt");

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"file not opened"<<endl;
    }
    else
    {
        while(! file.atEnd())
        {
            data = file.readLine();
            data.remove("\r\n");
            bool ok;
            int number = data.toInt(&ok, 10);
            listOfScores.push_back(number);
        }

        file.close();
    }



    return listOfScores;
}

void Game::saveScores(QString scores){

    QString data;
    QString fileName("highscores.txt");

    QFile file(fileName);
    file.close();


    if(!file.exists()){
        qDebug() << file.fileName() << "does not exists";
    }

    if(file.open(QIODevice::ReadWrite)){
        QTextStream txtStream(&file);

        txtStream << scores;
        file.close();

    }
    else{
        qDebug() << file.error();
        qDebug() << "Could not open the file";
    }


}


void Game::increaseScore(int addedScore) {
    m_score += addedScore;
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
            //items.swapItemsAt(i,j);
            items.swap(i,j);
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
                player->moveLeft();
                break;
            case Qt::Key_Right :
            case Qt::Key_D :
                player->moveRight();
                break;
            case Qt::Key_Space:
            case Qt::Key_Up:
            case Qt::Key_Z :
                if(!player->m_hasShot && !player->isOnJetpack()) {
                    player->m_hasShot = true;
                    auto *bullet = new Bullet(player->m_shootTimer);
                    bullet->setPos(player->x() + player->pixmap().width() / 2., player->y());
                    scene->addItem(bullet);

                    player->setPixmap(Resources::png("doodleShootG.png"));
                    if(!player->isFacingLeft()) {
                        player->setPixmap(player->pixmap().transformed(QTransform().scale(-1, 1)));
                    }
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
            default:
                break;
        }
    }
    if (player->y() + player->pixmap().height()>= WINDOW_HEIGHT) { // (Perdu)
        fallSound->play();
        rageSound->play();
        m_lost = true;
        timerEndGame->start(2000);
    }
}

void Game::jumpPlayer() { // Todo : séparer mort/vivant + appeler fonctions pour faciliter compréhension
    if(jumpThread->isRunning()) {
        if (player->isOnJetpack()) {
            player->setVelocityY(-10);
        } else if(m_lost) {
            player->setVelocityY(-4);
        }else {
            player->setVelocityY(player->getVelocityY() + GRAVITY);
        }

        if (player->y() < MAX_HEIGHT) { // Hauteur max, scroll

            if(!m_lost) {
                addPlatform();
                isScrolling = true;
                increaseScore();
            }
            player->moveVertical(MAX_HEIGHT);
            for (auto element : scene->items()) {
                if (dynamic_cast<Platform *>(element) || dynamic_cast<Bullet *>(element) ||
                    dynamic_cast<Monster *>(element) || dynamic_cast<Bonus *>(element)) {

                    if(!m_lost) {
                        element->setY(element->y() - player->getVelocityY());
                    }
                }
            }
        } else {
            // Scrool a little more to prevent scrolling on each jump if player doesn't move
            if (isScrolling) {
                isScrolling = false;
                player->moveVertical(player->y() + 1);
                for (auto element : scene->items()) {
                    if (dynamic_cast<Platform *>(element) || dynamic_cast<Bullet *>(element) ||
                        dynamic_cast<Monster *>(element) || dynamic_cast<Bonus *>(element)) {
                        element->setY(element->y() + 1);
                    }
                }
            }
        }
        if(m_lost) {
            for (auto element : scene->items()) {
                if (dynamic_cast<Platform *>(element) || dynamic_cast<Bullet *>(element) ||
                    dynamic_cast<Monster *>(element) || dynamic_cast<Bonus *>(element)) {
                    element->setY(element->y() + player->getVelocityY()*2);
                }
            }
        }
        for (auto element : scene->items()) {
            if (dynamic_cast<Platform *>(element) || dynamic_cast<Bonus *>(element) || dynamic_cast<Monster *>(element) ) {
                if(m_lost) {
                    if (element->y() < 0) { // Si plateforme/bonus/monstre au dessus de l'écran
                        scene->removeItem(element);
                        delete element;
                    }
                }
                else {
                    if (element->y() > WINDOW_HEIGHT) { // Si plateforme/bonus/monstre en dessous de l'écran
                        scene->removeItem(element);
                        delete element;
                    }
                }
            } else if (auto *bullet = dynamic_cast<Bullet *>(element)) {
                if(!m_lost) {
                    for (auto element2 : scene->collidingItems(bullet)) {
                        if (auto *monster = dynamic_cast<Monster *>(element2)) { // Monstre
                            scene->removeItem(monster);
                            increaseScore(200);
                            delete bullet;
                            if (shootMonsterSound->state() == QMediaPlayer::PlayingState) {
                                shootMonsterSound->setPosition(0);
                            } else if (shootMonsterSound->state() == QMediaPlayer::StoppedState) {
                                shootMonsterSound->play();
                            }
                        }
                    }
                }
                if (bullet->y() + bullet->pixmap().height() < 0) { // Si bullet  au dessus de l'écran
                    scene->removeItem(bullet);
                    delete bullet;
                }
            }
        }
        player->moveVertical(player->y() + player->getVelocityY());
        if (player->getVelocityY() > 0) {
            player->setFalling(true);
            if(!player->isHit()) {
                // On vérifie si on touche une plateforme
                for (auto element : scene->collidingItems(player)) {
                    if (auto *platform = dynamic_cast<Platform *>(element)) { // Rebond
                        // Si les pieds atteignent la moitié supérieure de la plateforme
                        if (player->y() + player->pixmap().height() - DOODLE_LAYOUT <
                            platform->y() + platform->pixmap().height() / 2) {
                            if (dynamic_cast<BreakingPlatform *>(platform)) {
                                auto *breaking = dynamic_cast<BreakingPlatform *>(platform);
                                breaking->launchBreak();
                            } else if (dynamic_cast<DisappearingPlatform *>(platform)) {
                                player->bounce(-5);
                                scene->removeItem(platform);
                                delete platform;

                                // Si le son est déjà lancé, remet à 0
                                if (bounceSound->state() == QMediaPlayer::PlayingState) {
                                    bounceSound->setPosition(0);
                                } else if (bounceSound->state() == QMediaPlayer::StoppedState) {
                                    bounceSound->play();
                                }
                            } else {
                                player->bounce(-5);

                                // Si le son est déjà lancé, remet à 0
                                if (bounceSound->state() == QMediaPlayer::PlayingState) {
                                    bounceSound->setPosition(0);
                                } else if (bounceSound->state() == QMediaPlayer::StoppedState) {
                                    bounceSound->play();
                                }
                            }

                        }
                    } else if (auto *monster = dynamic_cast<Monster *>(element)) { // Monstre
                        if (player->y() + player->pixmap().height() < monster->y() + monster->pixmap().height() / 2 + DOODLE_LAYOUT) {
                            monster->launchKill();
                            player->bounce(-7);
                            increaseScore(200);

                            if (jumpOnMonsterSound->state() == QMediaPlayer::PlayingState) {
                                jumpOnMonsterSound->setPosition(0);
                            } else if (jumpOnMonsterSound->state() == QMediaPlayer::StoppedState) {
                                jumpOnMonsterSound->play();
                            }
                        } else {
                            player->setHit(true);
                            player->setVelocityY(0);
                            break;
                        }
                    } else if (auto *bonus = dynamic_cast<Bonus *>(element)) { // Rebond
                        if (auto *spring = dynamic_cast<Spring *>(bonus)) {
                            if (player->y() + player->pixmap().height() <
                                spring->y() + spring->pixmap().height() / 2. + DOODLE_LAYOUT) {
                                player->bounce(-10);

                                // Si le son est déjà lancé, remet à 0
                                if (springSound->state() == QMediaPlayer::PlayingState) {
                                    springSound->setPosition(0);
                                } else if (springSound->state() == QMediaPlayer::StoppedState) {
                                    springSound->play();
                                }
                                spring->jump();
                            }
                        } else if (auto *jetpack = dynamic_cast<Jetpack *>(bonus)) {
                            scene->removeItem(jetpack);
                            player->setJetpack();
                            jetpackTimer->start(JETPACK_DURATION);
                            // Si le son est déjà lancé, remet à 0
                            if (jetpackSound->state() == QMediaPlayer::PlayingState) {
                                jetpackSound->setPosition(0);
                            } else if (jetpackSound->state() == QMediaPlayer::StoppedState) {
                                jetpackSound->play();
                            }
                        }
                        else if (auto *coin = dynamic_cast<Coin *>(bonus)) {
                            scene->removeItem(coin);
                            increaseScore(SCORE_COINS);
                            coinSound->play();
                        }
                    }
                }
            }
        } else {
            player->setFalling(false);
            // On vérifie si on touche un monstre
            for (auto element : scene->collidingItems(player)) {
                if (dynamic_cast<Monster *>(element)) {
                    if (!player->isOnJetpack()) {
                       player->setHit(true);
                       player->setVelocityY(0);
                        break;
                    }
                } else if (dynamic_cast<Jetpack *>(element)) {
                    if(!player->isOnJetpack()) {
                        scene->removeItem(element);
                        player->setJetpack();
                        jetpackTimer->start(JETPACK_DURATION);
                        // Si le son est déjà lancé, remet à 0
                        if (jetpackSound->state() == QMediaPlayer::PlayingState) {
                            jetpackSound->setPosition(0);
                        } else if (jetpackSound->state() == QMediaPlayer::StoppedState) {
                            jetpackSound->play();
                        }
                    }
                }
                else if (dynamic_cast<Coin *>(element)) {
                    scene->removeItem(element);
                    increaseScore(SCORE_COINS);
                    if (coinSound->state() == QMediaPlayer::PlayingState) {
                        coinSound->setPosition(0);
                    } else if (coinSound->state() == QMediaPlayer::StoppedState) {
                        coinSound->play();
                    }
                }
            }
        }
        if(!m_lost) {
            player->updatePixmap();
        }
    }
}

void Game::loose() {
    timerMove->stop();
    jumpThread->quit();
    jumpThread->wait();

    // Clear scene
    for (auto element : scene->items()) { // dynamic_cast<GameObject *>(element) ?
        if (dynamic_cast<Platform *>(element) || dynamic_cast<Monster *>(element) ||
            dynamic_cast<Bullet *>(element) || dynamic_cast<Player *>(element) || dynamic_cast<Bonus *>(element) ||dynamic_cast<QGraphicsTextItem*>(element)) {
            scene->removeItem(element);
            delete element;
        }
    }
    highscores();
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

void Game::stopJetpack() {
    player->removeJetpack();
}


