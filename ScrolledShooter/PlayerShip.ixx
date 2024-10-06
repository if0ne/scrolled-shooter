#pragma once
#include <SDL.h>

export module PlayerShip;

import GameObject;
import Utility;

export class PlayerShip : public GameObject {
private:
    float _targetY;

    float _velocityY;
    float _acceleration;
    float _prevSign;
    float _moveThreshold;

    float _fireRate;
    float _lastShotTime;
public:
    PlayerShip(float x, float y, float fireRate) 
        : GameObject(x, y, 150.0f, 75.0f)
        , _targetY(y)
        , _moveThreshold(_height / 4.0f)
        , _velocityY(0.0f)
        , _acceleration(1700.0f)
        , _prevSign(1.0f)
        , _fireRate(fireRate)
        , _lastShotTime(0.0)
    {}

    void Update(float dt) override;

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void TargetY(float y) {
        _targetY = y;
    }

    float TargetY() {
        return _targetY;
    }

    void Shoot();
};