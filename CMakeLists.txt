# cmake_minimum_required(VERSION <specify CMake version here>)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoodleJump main.cpp GameObject.cpp GameObject.h Moving.cpp Moving.h Platform.cpp Platform.h Bonus.cpp Bonus.h Hurts.cpp Hurts.h Bomb.cpp Bomb.h Monster.cpp Monster.h Player.cpp Player.h MovingPlatform.cpp MovingPlatform.h BasicPlatform.cpp BasicPlatform.h BreakingPlatform.cpp BreakingPlatform.h ExplodingPlatform.cpp ExplodingPlatform.h DisappearingPlatform.cpp DisappearingPlatform.h)