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
        _targetY = _baseY + Random(-400.0f, 400.0f);
        _targetY = std::min(_targetY, Game::kScreenHeight - 10.0f - _height);
    }

    _x += _velocityX * dt;
}