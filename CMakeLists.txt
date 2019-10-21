cmake_minimum_required(VERSION 3.14)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)
find_package(Qt5Widgets REQUIRED)

add_executable(DoodleJump main.cpp GameObject.cpp GameObject.h Moving.cpp Moving.h Platform.cpp Platform.h Bonus.cpp Bonus.h Hurts.cpp Hurts.h Bomb.cpp Bomb.h Monster.cpp Monster.h Player.cpp Player.h MovingPlatform.cpp MovingPlatform.h BasicPlatform.cpp BasicPlatform.h BreakingPlatform.cpp BreakingPlatform.h ExplodingPlatform.cpp ExplodingPlatform.h DisappearingPlatform.cpp DisappearingPlatform.h Bullet.cpp Bullet.h)

target_link_libraries(DoodleJump Qt5::Widgets)