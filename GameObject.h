#ifndef DOODLEJUMP_GAMEOBJECT_H
#define DOODLEJUMP_GAMEOBJECT_H

#include <QGraphicsPixmapItem>

class GameObject : public QGraphicsPixmapItem {

public:

    bool operator< (GameObject* a);

};



#endif //DOODLEJUMP_GAMEOBJECT_H
