#pragma once
#include <SDL.h>
#include <memory>

export module Bomber;

import Enemy;

export class Bomber : public Enemy { 
public:
    Bomber(float x, float y, float width, float height, float velocityX)
        : Enemy(x, y, width, height, velocityX)
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

    static std::shared_ptr<Bomber> CreateBig(float x, float y, float velocityX) {
        return std::make_shared<Bomber>(x, y, 200, 100, velocityX);
    }

    static std::shared_ptr<Bomber> CreateMedium(float x, float y, float velocityX) {
        return std::make_shared<Bomber>(x, y, 150, 70, velocityX);
    }
};