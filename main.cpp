#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

#include "Player.h"
#include "Bullet.h"

using namespace std;

int main(int argv, char **args) {

    QApplication app(argv, args);

    QGraphicsScene * scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(QApplication::applicationDirPath() + "/images/background.png")));
    Player * player = new Player();

    player->setPixmap(QPixmap(QApplication::applicationDirPath() + "/images/doodle.png"));

    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    return app.exec();
}