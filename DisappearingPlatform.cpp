#include "DisappearingPlatform.h"

DisappearingPlatform::DisappearingPlatform() : Platform("disappearingPlatform.png"){
}

DisappearingPlatform::DisappearingPlatform(float yMin, float yMax) : Platform("disappearingPlatform.png", yMin, yMax) {
}