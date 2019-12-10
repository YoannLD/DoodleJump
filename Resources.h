#ifndef CROCROJUMP_RESOURCES_H
#define CROCROJUMP_RESOURCES_H

#include <QtCore/QObject>

/**
 * Resources class.
 * This class is used to store a list that contains all the images useful to the game.
 * Whenever an image is called, if it is not in the list then we load it. Otherwise we get it in the list.
 * @author Yoann Le Dréan
 * @author Benoît Martel
 */
class Resources{

private:

    /*!
     * The explicit constructor of the Resources class.
     */
    explicit Resources();

    /*!
     * The instance of the resources class.
     */
    static Resources* m_instance;

    /*!
     * The map which contains each image in relation to their name.
     */
    std::map<QString, QPixmap> cache;

public:

    /*!
     * Method to load an image if it does not exist in the list otherwise to return the image directly from the list.
     * @param name the name to the image to get.
     * @return the image the we want.
     */
    static QPixmap png(const QString &name);
};


#endif //CROCROJUMP_RESOURCES_H