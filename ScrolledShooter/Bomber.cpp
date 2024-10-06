#pragma once
#include <SDL.h>

import Bomber;
import Game;
import Utility;

void Bomber::Update(float dt) {
    Enemy::Update(dt);
    _x += _velocityX * dt;
}

void Bomber::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
    SDL_SetRenderDrawColor(renderer, 215, 99, 128, 255);
    SDL_RenderFillRect(renderer, &rect);
}