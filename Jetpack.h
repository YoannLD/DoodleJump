#ifndef CROCROJUMP_JETPACK_H
#define CROCROJUMP_JETPACK_H

#include "Bonus.h"
#include "Platform.h"

/*!
 * Jetpack class.
 * This class allows you to manage the jetpack bonus.
 * The jetpack allows Croco to climb faster without being hit by monsters for a certain time.
 * Jetpack is a subclass of Bonus.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Jetpack : public Bonus {
public:

    /*!
     * Constructor of the class Jetpack.
     * @param p the platform on which the coin is linked
     */
    Jetpack(Platform* p);
};

#endif //CROCROJUMP_JETPACK_H
