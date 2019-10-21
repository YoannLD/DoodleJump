#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>

class Player : public QGraphicsRectItem{

public:
    void keyPressEvent(QKeyEvent * event) override;
};

#endif //DOODLEJUMP_PLAYER_H
