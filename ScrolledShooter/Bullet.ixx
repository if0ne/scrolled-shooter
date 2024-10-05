#include <SDL.h>

export module Bullet;

import GameObject;
import Utility;

export class Bullet : public GameObject {
private:
    float _velocityY;
    float _velocityX;
    float _acceleration;
public:
    Bullet(float x, float y, float velocityX)
        : GameObject(x, y, 50.0f, 50.0f)
        , _velocityX(velocityX)
        , _velocityY(0.0f)
        , _acceleration(50.0f)
    {}

    void Update(float dt) override {
        _x += _velocityX * dt;
        _y += _velocityY * dt;

        _velocityY += _acceleration * dt;
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 54, 54, 54, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};