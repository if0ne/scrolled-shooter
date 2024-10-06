#pragma once
#include <SDL.h>

import Meteor;
import Game;

void Meteor::Update(float dt) {
    _x += _velocityX * dt;
    _y += _velocityY * dt;

    if (IsIntersect(*Game::Instance().Player().get())) {
        Game::Instance().KillPlayer();
        return;
    }

    auto enemies = Game::Instance().Enemies();
    for (auto& enemy : enemies) {
        if (enemy->IsCollidable() && IsIntersect(*enemy.get())) {
            Game::Instance().DestroyEnemy(*enemy.get());
        }
    }

    if (_y > Game::kScreenHeight + _height / 2.0) {
        Game::Instance().DestroyMeteor(*this);
    }
}

void Meteor::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
    SDL_SetRenderDrawColor(renderer, 239, 83, 39, 255);
    SDL_RenderFillRect(renderer, &rect);
}