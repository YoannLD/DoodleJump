#include "Platform.h"

float Platform::multiplier = 1.f;

void Platform::incrementMultiplier() {
    ++multiplier;
}

void Platform::resetMultiplier() {
    multiplier = 1.f;
}
