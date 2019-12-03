#ifndef DOODLEJUMP_MONSTER_H
#define DOODLEJUMP_MONSTER_H

#include <QMediaPlayer>
#include <QTimer>
#include "Hurts.h"
#include "Moving.h"
#include "Platform.h"

class Monster : public QObject, public Hurts {
    Q_OBJECT
public:
    Monster(Platform* p);
    ~Monster();

    void kill();
    void launchKill();

public slots:
    void animation();
private:
    QTimer* killTimer;
    QTimer* animationTimer;
    int animation_state = 1;
};

#endif //DOODLEJUMP_MONSTER_H
