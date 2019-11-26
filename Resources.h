//
// Created by Benoît on 26/11/2019.
//

#ifndef DOODLEJUMP_RESOURCES_H
#define DOODLEJUMP_RESOURCES_H


#include <QtCore/QObject>

class Resources{

private:
    explicit Resources();
    static Resources* m_instance;
    std::map<QString, QPixmap> cache;

public:
    static QPixmap png(const QString &name);
};


#endif //DOODLEJUMP_RESOURCES_H
