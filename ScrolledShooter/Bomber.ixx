export module Bomber;

import Enemy;

export class Bomber : public Enemy { 
public:
    Bomber(float x, float y, float velocityX)
        : Enemy(x, y, 200.0f, 100.0f, velocityX)
    {
        _isCollidable = true;
    }

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
};