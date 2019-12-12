#ifndef CROCROJUMP_GAME_H
#define CROCROJUMP_GAME_H

#include <QGraphicsView>
#include "Platform.h"
#include <QMediaPlayer>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include "Player.h"


/*!
 * Game class.
 * This class allows you to manage the entire game, from the creation of platforms, to the detection of obstacles.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Game :  public QGraphicsView {
    Q_OBJECT
public:

    /*!
     * Constructor.
     */
    Game();

private:

    /*!
     * Play button instance.
     */
    QPushButton *buttonPlay;

    /*!
     * Exit button instance.
     */
    QPushButton *buttonQuit;

    /*!
     * Instance of the game scene.
     */
    QGraphicsScene *scene;

    /*!
     * Instance of the menu scene.
     */
    QGraphicsScene *menuScene;

    /*!
     * Instance of the highscores scene.
     */
    QGraphicsScene *highscoresScene;

    /*!
     *
     */
    QMediaPlayer* bounceSound ;

    /*!
     * Method that allows to create platforms on the game scene.
     */
    void addPlatform();

    /*!
     * Method that increases the player's score.
     */
    void increaseScore(int addedScore = 1);

    /*!
     * Method that sorts platforms.
     */
    static void quickSort(QList<Platform *> &items, int debut, int fin);

    /*!
     * Method which returns the platforms in collision with the platform passed in parameter.
     * @param platform the platform to be tested.
     * @return the list of platforms that collide with the platform passed in parameter.
     */
    QList<Platform *> collidingPlatforms(Platform *platform);

    /*!
     * Method that returns all the platforms present in the game scene.
     * @return the list of platforms present in the game scene.
     */
    QList<Platform *> getAllPlatforms();

    /*!
     * boolean which activates or not the creation of disappearing platform.
     */
    bool disappearingPlatformAllow = false;

    /*!
     * boolean which activates or not the creation of exploding platform.
     */
    bool explodingPlatformAllow = false;

    int multiplier = 50;

    /*!
     * minimum platform creation distance, evolves as the game progresses.
     */
    int dist_min = 0;

    /*!
     * maximum platform creation distance, evolves as the game progresses.
     */
    int dist_max = 0;

    /*!
     * max number of platforms that disappear by group, evolves over the game.
     */
    int disappearing_max = 0;

    /*!
     * max number of platforms exploding per group, evolves over the game.
     */
    int exploding_max = 0;

    /*!
     * boolean which indicates if the scene goes down.
     */
    bool isScrolling = false;

    /*!
     * boolean which indicates if it's an disappearing platform period
     */
    bool sectionDisappearingPlatform = false;
    /*!
     * number of disappearing platforms created in the period
     */
    int countNbDisappearingPlatform;
    /*!
     * number of disappearing platforms currently created in the period
     */
    int countNbDisappearingPlatformActual;

    /*!
     * boolean which indicates if it's an exploding platform period.
     */
    bool sectionExplodingPlatform = false;
    /*!
     * number of exploding platforms created in the period.
     */
    int countNbExplodingPlatform;
    /*!
     * number of exploding platforms currently created in the period.
     */
    int countNbExplodingPlatformActual;

    /*!
     * player score.
     */
    int m_score = 0;

    /*!
     * Player instance.
     */
    Player *player;

    /*!
     * text to display the current score.
     */
    QGraphicsTextItem *text;

    /*!
     * string that is used when calculating high scores.
     */
    QString temp = "";

    /*!
     * text for high scores.
     */
    QGraphicsTextItem *tableHighScore;

    /*!
     * calculation of the best scores.
     */
    void highscores();

    /*!
     * sound of the fall.
     */
    QMediaPlayer *fallSound;

    /*!
     * sound of the shoot.
     */
    QMediaPlayer *shootSound;

    /*!
     * sound of the spring.
     */
    QMediaPlayer *springSound;

    /*!
     * sound of the jetpack.
     */
    QMediaPlayer *jetpackSound;

    /*!
     * sound of the coin.
     */
    QMediaPlayer *coinSound;

    /*!
     * sound of the monster jump.
     */
    QMediaPlayer *jumpOnMonsterSound;

    /*!
     * sound of the monster shoot.
     */
    QMediaPlayer *shootMonsterSound;

    /*!
     * Method for calculating the number of platforms required for the scene.
     */
    void calculateNumberOfPlatform();

    /*!
     * Method that allows you to set up the player at the start of the game.
     */
    void setupPlayer();

    /*!
     * Method that allows you to go to the menu.
     */
    void menu();

    /*!
     * Timer for movements.
     */
    QTimer* timerMove;

    /*!
     * Timer for jumps.
     */
    QTimer* timerJump;

    /*!
     * Timer for the end game.
     */
    QTimer* timerEndGame;

    /*!
     * Thread for player jumps.
     */
    QThread* jumpThread;

    /*!
     * Method that generates a random number between 0 and 100.
     * @return a random number between 0 and 100.
     */
    static float generateRandom();

    /*!
     * Allows you to retrieve all the platforms on the stage on which you can jump.
     */
    QList<Platform *> getAllJumpablePlatforms();

private:

    /*!
     * Timer for jetpacks
     */
    QTimer* jetpackTimer;

    /*!
     * boolean that indicates if we lost.
     */
    bool m_lost = false;

public slots:

    /*!
     * A method to stop jetpack animation and its effects.
     */
    void stopJetpack();

    /*!
     * Method that moves the player.
     */
    void movePlayer();

    /*!
     * Method that allows you to blow the player.
     */
    void jumpPlayer();

private slots:

    /*!
     * Method to launch the game
     */
    void start();

    /*!
     * Method that triggers the end of the game
     */
    void loose();


    /*!
     * Method to save the score
     * @param scores contains the top three scores.
     */
    void saveScores(QString scores);

    /*!
     * Method for retrieving the best scores.
     * @return an integer list containing the scores.
     */
    std::list<int> getHighScore();
};

#endif //CROCROJUMP_GAME_H
