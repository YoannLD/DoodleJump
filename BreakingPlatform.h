#ifndef DOODLEJUMP_BREAKINGPLATFORM_H
#define DOODLEJUMP_BREAKINGPLATFORM_H

#include <QMediaPlayer>
#include "Platform.h"

class BreakingPlatform : public Platform {
public:
    BreakingPlatform();
    BreakingPlatform(float minY, float maxY);
    ~BreakingPlatform();
    void launchBreak();

private:
    QTimer* breakingTimer;
    QMediaPlayer* breakSound ;
    int state = 1;

public slots:
    void breaking();

};

#endif //DOODLEJUMP_BREAKINGPLATFORM_H
