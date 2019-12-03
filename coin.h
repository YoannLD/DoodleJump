//
// Created by Yoann on 03/12/2019.
//

#ifndef DOODLEJUMP_COIN_H
#define DOODLEJUMP_COIN_H

#include "Platform.h"
#include "Bonus.h"
#include <QTimer>

class Coin : public QObject, public Bonus {
    Q_OBJECT
public:
    Coin(Platform* p);
    ~Coin();
private:

    QTimer* animationTimer;
    int animation_state = 1;

public slots:
    void animation();
};
#endif //DOODLEJUMP_COIN_H
