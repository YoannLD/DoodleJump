#include <QApplication>
#include <QDebug>
#include <iostream>
#include "Game.h"

using namespace std;

int main(int argv, char **args) {


    QApplication app(argv, args);
    app.setWindowIcon(QIcon(":/favicon.ico"));


    Game * game = new Game();

    game->show();

   return app.exec();

}