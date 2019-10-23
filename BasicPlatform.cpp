#include "BasicPlatform.h"
#include <QApplication>
#include <QDebug>


BasicPlatform::BasicPlatform() {
    // --------- Loading pixmaps ---------
    auto* pixmap = new QPixmap();
    bool loaded = pixmap->load(QApplication::applicationDirPath() + "/images/basicPlatform.png");
    if(!loaded) {
        qDebug() << "Error loading : " + QApplication::applicationDirPath() + "/images/basicPlatform.png";
    }
    setPixmap(*pixmap);
}
