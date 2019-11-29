#include "Jetpack.h"
#include "Resources.h"
#include <qDebug>

Jetpack::Jetpack(Platform* platform) : Bonus(platform) {
    setPixmap(Resources::png("jetpack/jetpack.png"));
    setPos(getPlatform()->x() + getPlatform()->pixmap().width()/2. - pixmap().width()/2., getPlatform()->y() - pixmap().height());
    setZValue(140);
}
