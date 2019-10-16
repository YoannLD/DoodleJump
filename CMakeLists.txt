# cmake_minimum_required(VERSION <specify CMake version here>)
project(DoodleJump)

set(CMAKE_CXX_STANDARD 14)

add_executable(DoodleJump Sources/main.cpp Sources/GameObject.cpp Headers/GameObject.h Sources/Moving.cpp Headers/Moving.h Sources/Platform.cpp Headers/Platform.h Sources/Bonus.cpp Headers/Bonus.h Sources/Hurts.cpp Headers/Hurts.h Sources/Bomb.cpp Headers/Bomb.h Sources/Monster.cpp Headers/Monster.h Sources/Player.cpp Headers/Player.h Sources/MovingPlatorm.cpp Headers/MovingPlatorm.h Sources/BasicPlatform.cpp Headers/BasicPlatform.h Sources/BreakingPlatform.cpp Headers/BreakingPlatform.h Sources/ExplodingPlatform.cpp Headers/ExplodingPlatform.h Sources/DisappearingPlatform.cpp Headers/DisappearingPlatform.h)