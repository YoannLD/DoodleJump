#ifndef DOODLEJUMP_BULLET_H
#define DOODLEJUMP_BULLET_H

#include <QObject>
#include "Moving.h"

class Bullet : public QObject, public Moving {
    Q_OBJECT
public:
    Bullet();
public slots:
    void move();
};

#endif //DOODLEJUMP_BULLET_H
