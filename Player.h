#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>

class Player : public Moving{

public:
    void keyPressEvent(QKeyEvent * event) override;
public slots:
    void move() override;
};

#endif //DOODLEJUMP_PLAYER_H
