#include <QApplication>
#include <QDebug>
#include <iostream>
#include "Game.h"

using namespace std;

int main(int argv, char **args) {


    QApplication app(argv, args);


    Game * game = new Game();

    game->show();

   return app.exec();

}