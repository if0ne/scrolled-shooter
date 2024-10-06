export module Bullet;

import GameObject;
import Utility;

export enum class HitLayer {
    Enemy,
    Player
};

export class Bullet : public GameObject {
private:
    float _velocityY;
    float _velocityX;
    float _acceleration;
    HitLayer _hitLayer;
public:
    Bullet(float x, float y, float velocityX, HitLayer hitLayer)
        : GameObject(x, y, 50.0f, 10.0f)
        , _velocityX(velocityX)
        , _velocityY(0.0f)
        , _acceleration(50.0f)
        , _hitLayer(hitLayer)
    {}

    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

    HitLayer HitLayer() const {
        return _hitLayer;
    }
};