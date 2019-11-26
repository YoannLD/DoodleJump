//
// Created by Benoît on 26/11/2019.
//

#include <QtGui/QPixmap>
#include "Resources.h"


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
        QPixmap pix(":/images/" + name);
        m_instance->cache[key] = pix;
        return pix;
    }

}
