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

    void Update(float dt) override;

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 99, 99, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};