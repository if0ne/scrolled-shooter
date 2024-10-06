#include <SDL.h>
#include <memory>

import Fighter;
import Game;
import Bullet;
import Utility;

void Fighter::Update(float dt) {
    Enemy::Update(dt);

    auto bullets = Game::Instance().Bullets();

    _targetY = _playerShip->Y();

    for (auto& bullet : bullets) {
        if (bullet->HitLayer() == HitLayer::Enemy) {
            if ((_x - _playerShip->X()) / 2.0 > _x - bullet->X()) {
                _targetY = bullet->Y() - 200.0f;
            }
        }
    }

    float delta = _targetY - _y;

    if (abs(static_cast<int>(delta)) > 1) {
        _y = Lerp(_y, _targetY, dt);
    }

    _x += _velocityX * dt;

    float tick = SDL_GetTicks64() / 1000.0;
    float elapsed = (tick - _lastShotTime);

    if (elapsed > _fireRate) {
        Game::Instance().SpawnBullet(std::make_shared<Bullet>(
            _x - _width / 2.0 - 25,
            _y,
            -600.0,
            HitLayer::Player
        ));
        _lastShotTime = tick;
    }


}