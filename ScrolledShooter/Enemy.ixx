#pragma once
#include <SDL.h>

export module Enemy;

import GameObject;
import Utility;

export class Enemy : public GameObject {
protected:
    float _velocityX;
    bool _isBulletCollidable;
public:
    Enemy(float x, float y, float width, float height, float velocityX)
        : GameObject(x, y, width, height)
        , _velocityX(velocityX)
        , _isBulletCollidable(false)
    {}

    void Update(float dt) override;

    bool IsBulletCollidable() const {
        return _isBulletCollidable;
    }
};