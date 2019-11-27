#include "Spring.h"
#include "Resources.h"
#include <qDebug>

Spring::Spring(BasicPlatform* platform) {
    m_platform = platform;
    setPixmap(Resources::png("spring/spring1.png"));
    setPos(platform->x() + platform->pixmap().width()/2 - pixmap().width()/2, m_platform->y() - pixmap().height());
    setZValue(140);
}

void Spring::jump() {
    setPixmap(Resources::png("spring/spring2.png"));
    setY(m_platform->y() - pixmap().height());
    setZValue(140);
}
