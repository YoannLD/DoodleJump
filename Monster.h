#ifndef CROCROJUMP_MONSTER_H
#define CROCROJUMP_MONSTER_H

#include <QMediaPlayer>
#include <QTimer>
#include "Hurts.h"
#include "Moving.h"
#include "Platform.h"

/*!
 * Class monster.
 * This class creates a monster object. This monster is on a platform.
 * To kill him we can use the bullets or jump on his head.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Monster : public QObject, public Hurts {
    Q_OBJECT

public:

    /*!
     * Constructor of the monster class.
     * @param p the platform on which the monster is linked
     */
    Monster(Platform* p);

    /*!
     * Destructor.
     * Also delete the two timers corresponding to his animation and his death.
     */
    ~Monster();

    /*!
     * Method that has each call made the monster go down (it dies).
     */
    void kill();

    /*!
     * Method to launch the timer that animates the death of the monster.
     */
    void launchKill();

public slots:

    /*!
    * Method to change the image of the monster to have an animation.
    */
    void animation();
private:

    /*!
     * The timer to his death.
     */
    QTimer* killTimer;

    /*!
     * The timer to his animation.
     */
    QTimer* animationTimer;

    /*!
     * Specify the state of the monster animation.
     */
    int animation_state = 1;
};

#endif //CROCROJUMP_MONSTER_H