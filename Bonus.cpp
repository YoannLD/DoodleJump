#include "Bonus.h"
#include <qDebug>


Bonus::Bonus(Platform* platform){
    m_platform = platform;
}

Platform* Bonus::getPlatform() {
    return m_platform;
}
