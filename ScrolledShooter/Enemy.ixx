#pragma once
#include <SDL.h>

export module Enemy;

import GameObject;
import Utility;

export class Enemy : public GameObject {
private:
    float _velocityX;
    bool _isCollidable;
public:
    Enemy(float x, float y, float width, float height, float velocityX)
        : GameObject(x, y, width, height)
        , _velocityX(velocityX)
        , _isCollidable(false)
    {}

    bool IsCollidable() const {
        return _isCollidable;
    }
};