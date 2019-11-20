#ifndef DOODLEJUMP_BULLET_H
#define DOODLEJUMP_BULLET_H

#include <QObject>
#include "Moving.h"

class Bullet : public QObject, public Moving {
    Q_OBJECT
public:
    Bullet(QTimer* timer);
public slots:
    void move();
};

#endif //DOODLEJUMP_BULLET_H
