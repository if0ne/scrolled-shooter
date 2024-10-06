export module Fighter;

#pragma once
#include <memory>

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
    void Render(SDL_Renderer* renderer) override;
};