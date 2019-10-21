#ifndef DOODLEJUMP_BULLET_H
#define DOODLEJUMP_BULLET_H

#include <QObject>
#include <QGraphicsRectItem>

class Bullet : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Bullet();
public slots:
    void move();
};

#endif //DOODLEJUMP_BULLET_H
