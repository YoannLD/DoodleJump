#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "GameObject.h"

class Platform : public GameObject {

public:
    static float multiplier;
    Platform(const QString& path);
    Platform(const QString& path, float yMin, float yMax);
protected:
    QPixmap* pixmap;
};

#endif //DOODLEJUMP_PLATFORM_H
