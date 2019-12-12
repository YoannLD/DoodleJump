#ifndef CROCROJUMP_PLATFORM_H
#define CROCROJUMP_PLATFORM_H

#include "GameObject.h"

/*!
 * Platform class.
 * This class is used to create a platform based on the type of platform requested.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Platform : public QObject, public GameObject {
Q_OBJECT
public:

    /*!
     * Create a platform with the path of the image. That of the desired platform.
     * @param path the path of the platform image
     */
    Platform(const QString& path);

    /**
     * Create a platform by specifying the limits within which it must be in the scene.
     * The position of the platform is random.
     * @param path the path of the platform image
     * @param yMin the y min position of the platform
     * @param yMax the y max position of the platform.
     */
    Platform(const QString& path, float yMin, float yMax);

};

#endif //CROCROJUMP_PLATFORM_H
