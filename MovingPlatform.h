#ifndef CROCROJUMP_MOVINGPLATFORM_H
#define CROCROJUMP_MOVINGPLATFORM_H

#include "Platform.h"
#include "Moving.h"

class MovingPlatform : public Platform, public Moving {
public:
    MovingPlatform();

    MovingPlatform(float yMin, float yMax);
    void addAssociatedItem(GameObject* item);

    ~MovingPlatform();
private:
    QTimer * movingTimer;
    enum direction {LEFT, RIGHT};
    direction state;
    QList<GameObject*> associatedItems;

    void moveLeft();
    void moveRight();

public slots:
    void move();
};

#endif //CROCROJUMP_MOVINGPLATFORM_H
