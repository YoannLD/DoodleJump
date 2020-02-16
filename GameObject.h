#ifndef CROCROJUMP_GAMEOBJECT_H
#define CROCROJUMP_GAMEOBJECT_H

#include <QGraphicsPixmapItem>

/*!
 * Class GameObject.
 * This class is a subclass of QGraphicsPixmapItem.
 * All objects using images will be sub objects of this class.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class GameObject : public QGraphicsPixmapItem {

public:
    /*!
     * Overdefinition of the lower comparison operator. This over-definition makes it possible to compare if the
     * position of an object is less than another passed as a parameter.
     * @param a the other object on which to compare
     * @return true if the position of the current object is less than the object passed as a parameter.
     */
    bool operator< (GameObject* a);

};

#endif //CROCROJUMP_GAMEOBJECT_H