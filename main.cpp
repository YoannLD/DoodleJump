#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <iostream>

#include "Player.h"

using namespace std;

int main(int argv, char **args) {

    QApplication app(argv, args);

    QGraphicsScene * scene = new QGraphicsScene();
    QPixmap backgroundPixmap = QPixmap();
    bool backgroundLoaded = backgroundPixmap.load(QApplication::applicationDirPath() + "/images/background.png");
    if(!backgroundLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/background.png";
    }
    scene->setBackgroundBrush(QBrush(backgroundPixmap));

    Player * player = new Player();
    QPixmap doodlePixmap = QPixmap();
    bool doodleLoaded = doodlePixmap.load(QApplication::applicationDirPath() + "/images/doodle.png");
    if(!doodleLoaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/doodle.png";
    }
    player->setPixmap(doodlePixmap);

    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    return app.exec();

}