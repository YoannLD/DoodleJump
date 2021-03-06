#ifndef CROCROJUMP_CONSTS_H
#define CROCROJUMP_CONSTS_H

#include <QPixmap>

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;
static const int MAX_HEIGHT = WINDOW_HEIGHT/2;
static const int BORDER_LAYOUT = 360;

// Game param

static const int BULLET_SPEED = 3;
static const int MONSTER_SPAWN_PROB = 1;
static const int DISAPPEARING_PLATFORM_PROB = 2; // 2%
static const int EXPLODING_PLATFORM_PROB = 10; // 2%
static const float GRAVITY = 0.1;
static const float DIST_MAX = 110.0;

static const int BREAKING_PLATFORM_PROB = 15; // 25%
static const int MOVING_PLATFORM_PROB   = 15; // 15%
static const int SPRING_PROB = 2;
static const float JETPACK_PROB = 0.1;
static const int COIN_PROB = 2;
static const int JETPACK_DURATION = 3000;
static const int JETPACK_LAYOUT = 9;
static const int DOODLE_LAYOUT = 8;
static const int SCORE_COINS = 100;

#endif //CROCROJUMP_CONSTS_H
