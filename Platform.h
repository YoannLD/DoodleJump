#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "GameObject.h"

class Platform : public QObject, public GameObject {
Q_OBJECT
public:
    static float multiplier;
    Platform(const QString& path);
    Platform(const QString& path, float yMin, float yMax);

    double frand_a_b(float a, float b);
};

#endif //DOODLEJUMP_PLATFORM_H
