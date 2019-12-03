#include "GameObject.h"
#include "QDebug"

bool GameObject::operator<(GameObject* a) {
    return y() > a->y();
}

