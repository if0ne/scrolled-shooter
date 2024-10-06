#include <SDL.h>
#include <memory>

import PlayerShip;

import Game;
import Bullet;

void PlayerShip::Shoot() {
    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastShotTime);

    if (elapsed > _fireRate) {
        Game::Instance().SpawnBullet(std::make_shared<Bullet>(_x + _width / 2.0 + 25, _y, 300.0));
        _lastShotTime = tick;
    }
}