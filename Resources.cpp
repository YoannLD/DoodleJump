#include <QtGui/QPixmap>
#include <iostream>
#include "Resources.h"
using namespace std;

Resources* Resources::m_instance = nullptr;

Resources::Resources() = default;

QPixmap Resources::png(const QString &name) {

    if(m_instance == nullptr)
        m_instance = new Resources();

    auto key = QString("%1").arg(name);
    auto find = m_instance->cache.find(key);
    if (find != m_instance->cache.end()) {
        return find->second;
    } else {
        try {
            QPixmap pix;
            if(!pix.load(":/images/" + name)) {
                throw QString(name + " n'existe pas !");
            }
            m_instance->cache[key] = pix;
            return pix;
        }
        catch(QString e) {
            cerr << e.toStdString() << endl;
        }
    }

}
