#ifndef CROCROJUMP_BREAKINGPLATFORM_H
#define CROCROJUMP_BREAKINGPLATFORM_H

#include <QMediaPlayer>
#include "Platform.h"

/*!
 * Class BreakingPlatform. Manage breaking platforms.
 * BreakingPlatform is a subclass of Platform.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class BreakingPlatform : public Platform {
public:

    /*!
     * Constructor of the BreakingPlatform class.
     * Create a breaking platform which breaks as soon as we jump on it. We call the super platform builder to create the platform.
     */
    BreakingPlatform();

    /*!
     * Constructor of the BreakingPlatform class.
     * Create a breaking platform which breaks as soon as we jump on it. We call the super platform builder to create the platform.
     * @param minY the minimum y position to which the platform should be positioned.
     * @param maxY the maximum y position to which the platform should be positioned.
     */
    BreakingPlatform(float minY, float maxY);

    /*!
     * The destructor.
     */
    ~BreakingPlatform();

    /*!
     * Method that starts the timer that will break the platform.
     */
    void launchBreak();

private:

    /*!
     * The timer that breaks more and more the platform over the tics.
     */
    QTimer* breakingTimer;

    /**
     * The sound object that makes the crackling sound of the platform.
     */
    QMediaPlayer* breakSound ;

    /**
     * The state where the platform is.
     */
    int state = 1;

public slots:

    /**
     * Method that is called at each timer ticks to break the platform.
     */
    void breaking();

};

#endif //CROCROJUMP_BREAKINGPLATFORM_H
