#pragma once
#include <SDL.h>

export module Meteor;

import GameObject;

export class Meteor : public GameObject {
private:
    float _velocityX;
    float _velocityY;
public:
    Meteor(float x, float y, float velocityX, float velocityY)
        : GameObject(x, y, 100.0f, 100.0f)
        , _velocityX(velocityX)
        , _velocityY(velocityY)
    {}

    void Update(float dt) override;

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 239, 83, 39, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};