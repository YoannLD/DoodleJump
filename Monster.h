#ifndef DOODLEJUMP_MONSTER_H
#define DOODLEJUMP_MONSTER_H

#include <QMediaPlayer>
#include <QTimer>
#include "Hurts.h"
#include "Moving.h"
#include "BasicPlatform.h"

class Monster : public QObject, public Hurts {
    Q_OBJECT
public:
    Monster(BasicPlatform* p);
    void kill();
    void launchKill();
    void getShot();
private:
    QTimer* killTimer;
    QMediaPlayer* jumpSound ;
    QMediaPlayer* dieSound ;
};

#endif //DOODLEJUMP_MONSTER_H
