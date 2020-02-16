#include <QApplication>
#include <iostream>
#include "Game.h"

using namespace std;


int main(int argv, char **args) {
    qputenv("QT_DEVICE_PIXEL_RATIO", "0");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication app(argv, args);
    app.setWindowIcon(QIcon(":/favicon.ico"));

    Game * game = new Game();

    game->show();

   return app.exec();

}