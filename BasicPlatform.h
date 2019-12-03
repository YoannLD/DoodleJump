#ifndef DOODLEJUMP_BASICPLATFORM_H
#define DOODLEJUMP_BASICPLATFORM_H

#include "Platform.h"

/**
 * Class BasicPlatform. Manage basic platforms.
 * BasicPlatform is a subclass of Platform.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class BasicPlatform : public Platform {
public:

    /*!
     * Constructor of the BasicPlatform class.
     * Create a basic (green) platform that has no properties. We call the super platform builder to create the platform.
     */
    BasicPlatform();

    /*!
     * Constructor of the BasicPlatform class.
     * Create a basic (green) platform that has no properties. We call the super platform builder to create the platform.
     * @param yMin the minimum y position to which the platform should be positioned.
     * @param yMax the maximum y position to which the platform should be positioned.
     */
    BasicPlatform(float minY, float maxY);
};


#endif //DOODLEJUMP_BASICPLATFORM_H