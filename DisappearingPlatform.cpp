#include "DisappearingPlatform.h"

DisappearingPlatform::DisappearingPlatform() : Platform(":/images/disappearingPlatform.png"){

}

DisappearingPlatform::DisappearingPlatform(float yMin, float yMax) : Platform(":/images/disappearingPlatform.png", yMin, yMax) {

}
