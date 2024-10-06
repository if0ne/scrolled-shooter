#pragma once
#include <SDL.h>

export module Bird;

import Enemy;

export class Bird : public Enemy {
public:
    Bird(float x, float y, float velocityX) : Enemy(x, y, 50.0f, 50.0f, velocityX)
    {}

    void Update(float dt) override {
        Enemy::Update(dt);

        _x += _velocityX * dt;
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 99, 99, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};