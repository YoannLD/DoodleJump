#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Moving.h"

class Player : public Moving{
public:
    void keyPressEvent(QKeyEvent * event);

};

#endif //DOODLEJUMP_PLAYER_H
