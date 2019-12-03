cmake_minimum_required(VERSION 3.1.0)
project(CrocroJump)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)
add_executable(CrocroJump main.cpp GameObject.cpp GameObject.h Moving.cpp Moving.h Platform.cpp Platform.h Bonus.cpp Bonus.h Hurts.cpp Hurts.h Bomb.cpp Bomb.h Monster.cpp Monster.h Player.cpp Player.h MovingPlatform.cpp MovingPlatform.h BasicPlatform.cpp BasicPlatform.h BreakingPlatform.cpp BreakingPlatform.h ExplodingPlatform.cpp ExplodingPlatform.h DisappearingPlatform.cpp DisappearingPlatform.h Bullet.cpp Bullet.h Game.cpp Game.h consts.h resources.qrc Spring.cpp Spring.h Jetpack.cpp Jetpack.h Resources.cpp Resources.h coin.cpp coin.h)

target_link_libraries(CrocroJump Qt5::Widgets Qt5::Multimedia)

