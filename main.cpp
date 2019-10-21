#include <QApplication>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Player.h"

using namespace std;

int main(int argv, char **args) {

    QApplication app(argv, args);

    QGraphicsScene * scene = new QGraphicsScene();

    Player * player = new Player();
    player->setRect(0,0,100,100);

    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    QGraphicsView *view = new QGraphicsView(scene);
    view->show();



    return app.exec();

}