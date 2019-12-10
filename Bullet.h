#ifndef CROCROJUMP_BULLET_H
#define CROCROJUMP_BULLET_H

#include <QObject>
#include "Moving.h"

/*!
 * Class Bullet. Manage bullet in the game.
 * Bullet is a subclass of Moving.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Bullet : public QObject, public Moving {
    Q_OBJECT
public:
    /*!
     * Constructor of the bullet class.
     * @param timer that triggers the bullet movement
     */
    Bullet(QTimer* timer);
public slots:

    /**
     * Method that moves the y position of the bullet in the game
     */
    void move();
};

#endif //CROCROJUMP_BULLET_H
