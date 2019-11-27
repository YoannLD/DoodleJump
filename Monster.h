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
    ~Monster();

    void kill();
    void launchKill();
    void getShot();

public slots:
    void animation();
private:
    QTimer* killTimer;
    QTimer* animationTimer;
    QMediaPlayer* jumpSound ;
    QMediaPlayer* dieSound ;
    int animation_state = 1;
};

#endif //DOODLEJUMP_MONSTER_H
