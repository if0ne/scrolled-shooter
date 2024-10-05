#include <SDL.h>
#include <iostream>

export module PlayerShip;

import GameObject;

export class PlayerShip : public GameObject {
private:
    
public:
    PlayerShip(float x, float y) : GameObject(x, y, 250, 100)
    {}

    void Update(float dt) override {
        // todo: moving
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

    }
};