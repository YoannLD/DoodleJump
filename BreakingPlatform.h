#ifndef DOODLEJUMP_BREAKINGPLATFORM_H
#define DOODLEJUMP_BREAKINGPLATFORM_H

#include "Platform.h"

class BreakingPlatform : public Platform {
public:
    BreakingPlatform();
    void launchBreak();

private:
    QTimer* breakingTimer;
    int state = 1;

public slots:
    void breaking();

};

#endif //DOODLEJUMP_BREAKINGPLATFORM_H
