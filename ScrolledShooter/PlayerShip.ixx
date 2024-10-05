#include <SDL.h>
#include <iostream>

export module PlayerShip;

import GameObject;

export class PlayerShip : public GameObject {
private:
    float _targetY;
    float _velocityY = 0.0;
    float _acceleration = 1.0;
    int _speed = 1.0;
    int _fireRate;
    int _lastShotTime;
public:
    PlayerShip(float x, float y) : GameObject(x, y, 250, 100), _targetY(y)
    {}

    void Update(float dt) override {
        _y = dt * _targetY + (1 - dt) * _y;

        
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x - _width / 2, _y - _height / 2, _width, _height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void Shoot() {
        // todo: shoot
        std::cout << "Shoot" << std::endl;
    }

    void TargetY(float y) {
        _targetY = y;
    }
};