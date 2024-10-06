#pragma once
#include <SDL.h>

export module Bird;

import Enemy;
import Utility;

export class Bird : public Enemy {
private:
    float _baseY;
    float _targetY;
public:
    Bird(float x, float y, float velocityX) 
        : Enemy(x, y, 50.0f, 50.0f, velocityX)
        , _baseY(y)
        , _targetY(y)
    {}

    void Update(float dt) override {
        Enemy::Update(dt);

        float delta = _targetY - _y;

        if (abs(static_cast<int>(delta)) > 1) {
            _y = Lerp(_y, _targetY, 2.0 * dt);
        } else {
            _targetY = _baseY + Random(-50.0, 50.0);
        }

        _x += _velocityX * dt;
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 99, 99, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};