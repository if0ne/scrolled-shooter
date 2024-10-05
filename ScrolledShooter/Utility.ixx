#include <SDL.h>

export module Utility;

export float Lerp(float v0, float v1, float t) {
    return (1.0 - t) * v0 + t * v1;
}

export float Sign(float v) {
    return copysign(1.0, v);
}