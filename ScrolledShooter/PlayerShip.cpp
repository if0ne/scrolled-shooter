#include <SDL.h>
#include <memory>

import PlayerShip;

import Game;
import Bullet;
import Utility;

void PlayerShip::Update(float dt) {
    float delta = _targetY - _y;
    float sign = Sign(delta);

    // Takes the speed away in the other direction
    if (_prevSign > 0.0 && sign < 0.0) {
        _velocityY = 0.0;
    }
    else if (_prevSign < 0.0 && sign > 0.0) {
        _velocityY = 0.0;
    }

    _prevSign = sign;

    if (abs(static_cast<int>(delta)) > _moveThreshold) {
        _velocityY += dt * _acceleration * sign;
    }

    _y += _velocityY * dt;

    if (_y + _height / 2 >= Game::kScreenHeight - 10.0) {
        Game::Instance().KillPlayer();
    }
}

void PlayerShip::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void PlayerShip::Shoot() {
    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastShotTime);

    if (elapsed > _fireRate) {
        Game::Instance().SpawnBullet(std::make_shared<Bullet>(
            _x + _width / 2.0 + 25,
            _y, 
            600.0, 
            HitLayer::Enemy
        ));
        _lastShotTime = tick;
    }
}