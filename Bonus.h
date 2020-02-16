#ifndef CROCROJUMP_BONUS_H
#define CROCROJUMP_BONUS_H

#include "GameObject.h"
#include "Platform.h"

/*!
 * Bonus class.
 * This class allows you to manage all the bonuses of the game.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Bonus : public GameObject {
    public:

        /*!
         * Constructor of the Bonus class.
         * We must provide a platform on which the object rests.
         * @param p the platform on which the object is placed.
         */
        Bonus(Platform* p);

        /*!
         * Get the platform on which the object is placed.
         * @return the platform on which the object is placed.
         */
        Platform* getPlatform();

    private:

        /*!
         * the platform on which the object is placed.
         */
        Platform* m_platform;
};

#endif //CROCROJUMP_BONUS_H