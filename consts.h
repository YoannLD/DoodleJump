//
// Created by Benoît on 21/10/2019.
//

#ifndef DOODLEJUMP_CONSTS_H
#define DOODLEJUMP_CONSTS_H

#include <QPixmap>

// Windows params
static const int WINDOW_WIDTH = 400;
static const int WINDOW_HEIGHT = 600;

// Game param

static const int BULLET_SPEED = 1;
static const int MONSTER_SPAWN_PROB = 2; // 2%
static const int DISAPPEARING_PLATFORM_PROB = 2; // 2%
static const int EXPLODING_PLATFORM_PROB = 10; // 2%
static const int MAX_HEIGHT = WINDOW_HEIGHT/2;
static const float GRAVITY = 0.1;
static const float DIST_MAX = 110.0;

static const int BREAKING_PLATFORM_PROB = 15; // 25%
static const int MOVING_PLATFORM_PROB   = 15; // 15%
static const int SPRING_PROB = 2;

#endif //DOODLEJUMP_CONSTS_H
