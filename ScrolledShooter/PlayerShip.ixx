#include <SDL.h>

export module PlayerShip;

import GameObject;
import Utility;

export class Game;

export class PlayerShip : public GameObject {
private:
    float _targetY;

    float _velocityY;
    float _acceleration;
    float _prevSign;
    float _moveThreshold;

    int _bulletsPerSecond;
    float _shootDelay;
    float _lastShotTime;
public:
    PlayerShip(float x, float y, int bulltesPerSecond) 
        : GameObject(x, y, 250.0f, 100.0f)
        , _targetY(y)
        , _moveThreshold(_height / 2.0f)
        , _velocityY(0.0f)
        , _acceleration(0.33f)
        , _prevSign(1.0f)
        , _bulletsPerSecond(bulltesPerSecond)
        , _shootDelay(1.0 / _bulletsPerSecond)
        , _lastShotTime(0.0)
    {}

    void Update(float dt) override {
        float delta = _targetY - _y;
        float sign = Sign(delta);

        // Takes the speed away in the other direction
        if (_prevSign > 0.0 && sign < 0.0) {
            _velocityY = 0.0;
        } else if (_prevSign < 0.0 && sign > 0.0) {
            _velocityY = 0.0;
        }

        _prevSign = sign;

        if (abs(static_cast<int>(delta)) > _moveThreshold) {
            _velocityY += dt * _acceleration * sign;
        }

        if (_y < _targetY && _y + _velocityY > _targetY
            || _y > _targetY && _y + _velocityY < _targetY) {
            _velocityY = 0.0;
            _y = _targetY;
        } else {
            _y += _velocityY;
        }
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void TargetY(float y) {
        _targetY = y;
    }

    void Shoot();
};