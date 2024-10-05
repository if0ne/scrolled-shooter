#include <SDL.h>
#include <memory>

import Bullet;
import Game;
import PlayerShip;

void PlayerShip::Shoot() {
    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastShotTime);

    if (elapsed > _shootDelay) {
        Game::Instance().SpawnBullet(std::make_shared<Bullet>(_x + _width / 2.0 + 50, _y, 250.0));
        _lastShotTime = tick;
    }
}