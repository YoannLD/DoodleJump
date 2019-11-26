#include "Jetpack.h"
#include <qDebug>

Jetpack::Jetpack(BasicPlatform* platform) {
    m_platform = platform;
    auto* jetpackPixmap = new QPixmap();
    bool jetpackLoaded = jetpackPixmap->load(":/images/jetpack.png");
    if(!jetpackLoaded) {
        qDebug() << "Error loading : :/images/jetpack.png";
    }
    setPixmap(*jetpackPixmap);
    delete jetpackPixmap;
    setPos(m_platform->x() + m_platform->pixmap().width()/2 - pixmap().width()/2, m_platform->y() - pixmap().height());
}
