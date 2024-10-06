#pragma once
#include <SDL.h>
#include <memory>

export module Fighter;

import Enemy;
import PlayerShip;
import Utility;

export class Fighter : public Enemy {
private:
    std::shared_ptr<PlayerShip> _playerShip;
    float _targetY;

    float _fireRate;
    float _lastShotTime;

public:
    Fighter(float x, float y, float velocityX, std::shared_ptr<PlayerShip> playerShip)
        : Enemy(x, y, 150.0f, 75.0f, velocityX)
        , _playerShip(playerShip)
        , _fireRate(2.0f)
        , _lastShotTime(0.0)
        , _targetY(y)
    {
        _isCollidable = true;
    }

    void Update(float dt) override;

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 0, 99, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
};