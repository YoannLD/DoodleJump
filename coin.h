#ifndef CROCROJUMP_COIN_H
#define CROCROJUMP_COIN_H

#include "Platform.h"
#include "Bonus.h"
#include <QTimer>

/*!
 * Coin class.
 * This class allows you to manage coins.
 * Coin is a subclass of Bonus.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Coin : public QObject, public Bonus {
    Q_OBJECT

public:

    /*!
     * Constructor of the coin class.
     * @param p the platform on which the coin is linked
     */
    Coin(Platform* p);

    /*!
     * Destructor of the coin class.
     * It also removes the timer used to rotate the coin
     */
    ~Coin();
private:

    /*!
     * The timer used to animate the coin.
     */
    QTimer* animationTimer;

    /*!
     * Specify the state of the coin animation.
     */
    int animation_state = 1;

public slots:

    /*!
     * Method to change the image of the coin to have an animation.
     */
    void animation();
};
#endif //CROCROJUMP_COIN_H
