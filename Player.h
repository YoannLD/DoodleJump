#ifndef CROCROJUMP_PLAYER_H
#define CROCROJUMP_PLAYER_H

#include "Moving.h"
#include "consts.h"
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

/*!
 * Player class.
 * This class is used to manage all of the player's actions. Allows its creation and its destruction.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Player : public QObject, public Moving {
Q_OBJECT
public:

    /*!
     * Constructor.
     */
    Player();

    /*!
     * Destructor.
     */
    ~Player();

    /*!
     * Method that retrieves key press events.
     * @param event keys press
     */
    void keyPressEvent(QKeyEvent *event) override;

    /*!
     * Method that retrieves key release events.
     * @param event keys release
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /*!
     * Std list which contains all the events.
     */
    std::vector<int> m_events;

    /*!
     * boolean which indicates if the player is turned to the left.
     */
    bool m_facingLeft = true;

    /*!
     * if the player has shot.
     */
    bool m_hasShot = false;

    /*!
     * timer for the shoot.
     */
    QTimer *m_shootTimer;

    /*!
     * timer for the shooting pixmap.
     */
    QTimer *m_shootingPixmapTimer;

    /*!
     * timer for the jetpack update.
     */
    QTimer *m_jetpackUpdateTimer;

    /*!
     * timer for the jetpack fall.
     */
    QTimer *m_jetpackFallTimer;

    /*!
     * method which makes it possible to recover the velocity y of the player.
     */
    float getVelocityY();

    /*!
     * method which allows to change the velocity y of the player.
     * @param newVelocity the new velocity y
     */
    void setVelocityY(float newVelocity);

    /*!
     * method which allows to place the jetpack in the back of the player.
     */
    void setJetpack();

    /*!
     * method that removes the jetpack from the player's back.
     */
    void removeJetpack();

    /*!
     * Method to move the player to the left.
     */
    void moveLeft();

    /*!
     * Method to move the player to the right.
     */
    void moveRight();

    /*!
     * Method to move the player vertically.
     */
    void moveVertical(int newY);

    /*!
     * Method to find out if the jetpack is active.
     * @return true if the jetpack is active
     */
    bool isOnJetpack();

    /*!
     * Method to tell if the player is falling or not.
     * @param f true if the player is falling else false.
     */
    void setFalling(bool f);

    /*!
     * Method for determining if the player is looking to the left.
     * @return true if the player is looking to the left.
     */
    bool isFacingLeft();

    /*!
     * Method of knowing if the player is hit.
     * @return true if the player is hit.
     */
    bool isHit();

    /*!
     * Method to tell if the player is hit or not.
     * @param hit true if the player is hit, false is not.
     */
    void setHit(bool hit);
private:

    /*!
     * Player's velocity y.
     */
    float m_velocityY = 0;

    /*!
     * the jet-pack image.
     */
    QGraphicsPixmapItem* jetpack{};

    /*!
     * boolean to find out if the jetpack is on the player's back.
     */
    bool m_jetpack;

    /*!
     * integer to know the state of the jetpack.

     */
    int m_jetpackState;

    /*!
     * jetpack state iteration counter.
     */
    int m_jetpackCpt;

    /*!
     * to rotate the jetpack.
     */
    float m_rotationJetpack;

    /*!
     * boolean who says if we fall.
     */
    bool m_falling;

    /*!
     * boolean who says if we're hit.
     */
    bool m_isHit;

public slots:

    /*!
     * method that manages the bounce.
     * @param newVel the new velocity y to set the right bounce
     */
    void bounce(float newVel);

    /*!
     * Method which makes it possible to update the image of the player according to the various states of the game.
     */
    void updatePixmap();

    /*!
     * Method which makes it possible to update the image of the jetpack according to the various states of the game.
     */
    void updateJetpackPixmap();

    /*!
     * Method for managing the jet-pack when it falls.
     */
    void jetpackFall();
};

#endif //CROCROJUMP_PLAYER_H
