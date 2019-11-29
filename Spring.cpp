#include "Spring.h"
#include "Resources.h"
#include <qDebug>

Spring::Spring(Platform* platform) : Bonus(platform){
    setPixmap(Resources::png("spring/spring1.png"));
    setPos(getPlatform()->x() + getPlatform()->pixmap().width()/2. - pixmap().width()/2., getPlatform()->y() - pixmap().height());
    setZValue(99);
}

void Spring::jump() {
    setPixmap(Resources::png("spring/spring2.png"));
    setY(getPlatform()->y() - pixmap().height());
    setZValue(99);
}