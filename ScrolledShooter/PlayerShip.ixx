#include <SDL.h>

export module PlayerShip;

import GameObject;

export class PlayerShip : public GameObject {
private:
    
public:
    void Update(float dt) override {
        // todo: moving
    }

    void Render(SDL_Renderer* renderer) override {
        SDL_Rect rect = { _x, _y, _width, _height };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    void Shoot() {
        // todo: shoot
    }
};