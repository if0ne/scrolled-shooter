#pragma once
#include <SDL.h>
#include <algorithm>

import Bird;
import Game;
import Utility;


void Bird::Update(float dt) {
    Enemy::Update(dt);

    float delta = _targetY - _y;

    if (abs(static_cast<int>(delta)) > 1) {
        _y = Lerp(_y, _targetY, 2.0 * dt);
    }
    else {
        _targetY = _baseY + Random(-200.0f, 200.0f);
        _targetY = std::min(_targetY, Game::kScreenHeight - 10.0f - _height);
    }

    _x += _velocityX * dt;
}

void Bird::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
    SDL_SetRenderDrawColor(renderer, 99, 99, 128, 255);
    SDL_RenderFillRect(renderer, &rect);
}