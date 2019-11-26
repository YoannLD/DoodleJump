#include "Jetpack.h"
#include "Resources.h"
#include <qDebug>

Jetpack::Jetpack(BasicPlatform* platform) {
    m_platform = platform;
    setPixmap(Resources::png("jetpack/jetpack.png"));
    setPos(m_platform->x() + m_platform->pixmap().width()/2 - pixmap().width()/2, m_platform->y() - pixmap().height());
}
