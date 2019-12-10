#ifndef CROCROJUMP_DISAPPEARINGPLATFORM_H
#define CROCROJUMP_DISAPPEARINGPLATFORM_H

#include "Platform.h"

/*!
 * Class DisappearingPlatform. Manage disappearing platforms.
 * BreakingPlatform is a subclass of Platform.
 * This platform is deleted after one rebound. This platform is white.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class DisappearingPlatform : public Platform {

public:
    
    /*!
     * Constructor of the DisappearingPlatform class.
     * Create a disappearing platform which is deleted after one rebound.
     * We call the super platform builder to create the platform.
     */
    DisappearingPlatform();
    
    /*!
     * Constructor of the DisappearingPlatform class.
     * Create a disappearing platform which is deleted after one rebound.
     * We call the super platform builder to create the platform.
     * @param yMin the minimum y position to which the platform should be positioned.
     * @param yMax the maximum y position to which the platform should be positioned.
     */
    DisappearingPlatform(float yMin, float yMax);

};

#endif //CROCROJUMP_DISAPPEARINGPLATFORM_H
