#ifndef CROCROJUMP_MOVING_H
#define CROCROJUMP_MOVING_H

#include "GameObject.h"

/*!
 * Class Moving.
 * This class manage the moving object of the game.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Moving : public GameObject {
public:

    /*!
     * Method that moves an object to the left.
     */
    virtual void moveLeft() = 0;

    /*!
     * Method that moves an object to the right.
     */
    virtual void moveRight() = 0;
};

#endif //CROCROJUMP_MOVING_H
