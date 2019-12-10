#ifndef CROCROJUMP_EXPLODINGPLATFORM_H
#define CROCROJUMP_EXPLODINGPLATFORM_H

#include "Platform.h"

/*!
 * Class ExplodingPlatform. Manage exploding platforms.
 * ExplodingPlatform is a subclass of Platform.
 * This platform explodes after going over. This platform is yellow then red and then black
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class ExplodingPlatform : public Platform {
public:

    /*!
     * Constructor of the ExplodingPlatform class.
     * Create a exploding platform which explodes after going over. We call the super platform builder to create the platform.
     */
    ExplodingPlatform();

    /*!
     * Constructor of the ExplodingPlatform class.
     * Create a exploding platform which explodes after going over. We call the super platform builder to create the platform.
     * @param yMin the minimum y position to which the platform should be positioned.
     * @param yMax the minimum y position to which the platform should be positioned.
     */
    ExplodingPlatform(float yMin, float yMax);

    /*!
    * Method that starts the timer that will start the timer with delay to explode the platform.
    */
    void launchExplosing();

    /*!
     * Destructor of the ExplodingPlatform class.
     * It also removes the timer used to explode the platform.
     */
    ~ExplodingPlatform();

private:
    /*!
     * The timer used to explode the platform.
     */
    QTimer* explodingTimer;

    /*!
    * Specify the state of the exploding platform animation.
    */
    int state = 1;


public slots:

    /*!
    * Method to change the image of the exploding platform to have an animation.
    */
    void exploding();

    /*!
    * Method that starts the timer that will explode the platform.
    */
    void startTimer();
};

#endif //CROCROJUMP_EXPLODINGPLATFORM_H
