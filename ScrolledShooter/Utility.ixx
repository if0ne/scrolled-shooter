#pragma once
#include <SDL.h>
#include <random>

export module Utility;

export float Lerp(float v0, float v1, float t) {
    return (1.0 - t) * v0 + t * v1;
}

export float Random(float v1, float v2) {
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(v1, v2);
    return dis(e);
}

export float Sign(float v) {
    return copysign(1.0, v);
}