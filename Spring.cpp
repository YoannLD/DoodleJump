#include "Spring.h"
#include <qDebug>

Spring::Spring(BasicPlatform* platform) {
    m_platform = platform;
    auto* springPixmap = new QPixmap();
    bool springLoaded = springPixmap->load(":/images/spring/spring1.png");
    if(!springLoaded) {
        qDebug() << "Error loading : :/images/spring1.png";
    }
    setPixmap(*springPixmap);
    delete springPixmap;
    setPos(platform->x() + platform->pixmap().width()/2 - pixmap().width()/2, m_platform->y() - pixmap().height());
}

void Spring::jump() {
    auto* springPixmap = new QPixmap();
    bool springLoaded = springPixmap->load(":/images/spring/spring2.png");
    if(!springLoaded) {
        qDebug() << "Error loading : :/images/spring2.png";
    }
    setPixmap(*springPixmap);
    delete springPixmap;
    setY(m_platform->y() - pixmap().height());
}
