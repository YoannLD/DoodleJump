#ifndef CROCROJUMP_SPRING_H
#define CROCROJUMP_SPRING_H

#include "Bonus.h"
#include "Platform.h"

/*!
 * Spring class.
 * This class allows you to manage the spring bonus.
 * The spring allows Croco to jump higher
 * Spring is a subclass of Bonus.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Spring : public Bonus {
public:

    /*!
     * Constructor of the spring class.
     * @param p the platform on which the spring is linked
     */
    Spring(Platform* p);

    /*!
     * Method that is called when the spring is touched.
     * This method makes it possible to change the image of the spring.
     */
    void jump();
};
#endif //CROCROJUMP_SPRING_H
