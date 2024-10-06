#pragma once
#include <SDL.h>
#include <memory>

export module Bomber;

import Enemy;

export class Bomber : public Enemy { 
public:
    Bomber(float x, float y, float velocityX)
        : Enemy(x, y, 200.0f, 100.0f, velocityX)
    {
        _isBulletCollidable = true;
    }

    void Update(float dt) override {
        Enemy::Update(dt);
        _x += _velocityX * dt;
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 215, 99, 128, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};